#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <QQmlEngine>

#include "src/app/appcontroller.h"
#include "src/app/navigationmanager.h"

#include <android/log.h>
#include <qsqlerror.h>
#include <qsqlquery.h>

#include "src/features/nutrition/nutritionservice.h"
#include "src/features/nutrition/nutritionviewmodel.h"
#include "src/core/databasemanager.h"

void testInsertFood()
{
    QSqlDatabase tDb = DatabaseManager::database();

    QSqlQuery query(tDb);

    qDebug() << "TEST: Inserting sample foods into foods table...";

    query.prepare(R"(
        INSERT INTO foods(name, calories, protein, carbs, fat)
        VALUES (?, ?, ?, ?, ?)
    )");

    // Banana
    query.addBindValue("Banana");
    query.addBindValue(89.0);
    query.addBindValue(1.1);
    query.addBindValue(22.8);
    query.addBindValue(0.3);

    if(!query.exec())
        qWarning() << "Insert Banana failed:" << query.lastError().text();

    // Chicken
    query.prepare(R"(
        INSERT INTO foods(name, calories, protein, carbs, fat)
        VALUES (?, ?, ?, ?, ?)
    )");

    query.addBindValue("Chicken Breast");
    query.addBindValue(165.0);
    query.addBindValue(31.0);
    query.addBindValue(0.0);
    query.addBindValue(3.6);

    if(!query.exec())
        qWarning() << "Insert Chicken failed:" << query.lastError().text();

    // Rice
    query.prepare(R"(
        INSERT INTO foods(name, calories, protein, carbs, fat)
        VALUES (?, ?, ?, ?, ?)
    )");

    query.addBindValue("Rice");
    query.addBindValue(130.0);
    query.addBindValue(2.7);
    query.addBindValue(28.0);
    query.addBindValue(0.3);

    if(!query.exec())
        qWarning() << "Insert Rice failed:" << query.lastError().text();

    qDebug() << "TEST: Insert done.";

    // ===== TEST: Read back =====
    QSqlQuery readQuery(tDb);
    if(readQuery.exec("SELECT id, name, calories FROM foods"))
    {
        qDebug() << "TEST: Reading foods table:";
        while(readQuery.next())
        {
            qDebug() << "ID:"
                     << readQuery.value(0).toInt()
                     << "Name:"
                     << readQuery.value(1).toString()
                     << "Calories:"
                     << readQuery.value(2).toDouble();
        }
    }
    else
    {
        qWarning() << "Read foods failed:" << readQuery.lastError().text();
    }
}

static void runNutritionServiceTests()
{
    qDebug() << "================ SERVICE TEST START ================";

    DatabaseManager tDatabaseManager;
    NutritionService tService(&tDatabaseManager);

    qDebug() << "Current date:" << tService.getDate();

    // 1) Catalog food add
    const bool tAdded1 = tService.addCatalogFood("Banana", 89.0, 1.1, 22.8, 0.3);
    const bool tAdded2 = tService.addCatalogFood("Chicken Breast", 165.0, 31.0, 0.0, 3.6);
    const bool tAdded3 = tService.addCatalogFood("Rice", 130.0, 2.7, 28.0, 0.3);

    qDebug() << "addCatalogFood Banana:" << tAdded1;
    qDebug() << "addCatalogFood Chicken Breast:" << tAdded2;
    qDebug() << "addCatalogFood Rice:" << tAdded3;

    // 2) Catalog search test
    const QVariantList tSearchAll = tService.searchCatalogFoods("");
    qDebug() << "Catalog search all count:" << tSearchAll.size();
    for(const QVariant& tItem : tSearchAll)
    {
        qDebug() << "Catalog item:" << tItem.toMap();
    }

    const QVariantList tSearchBa = tService.searchCatalogFoods("Ba");
    qDebug() << "Catalog search 'Ba' count:" << tSearchBa.size();
    for(const QVariant& tItem : tSearchBa)
    {
        qDebug() << "Search 'Ba' item:" << tItem.toMap();
    }

    // 3) Daily meal test
    tService.addMeal("Breakfast");
    tService.addMeal("Lunch");

    qDebug() << "Meal count after addMeal:" << tService.mealCount();

    // 4) Insert food into meal
    tService.addFood(0, "Banana", 89.0, 1.1, 22.8, 0.3);
    tService.addFood(0, "Rice", 130.0, 2.7, 28.0, 0.3);
    tService.addFood(1, "Chicken Breast", 165.0, 31.0, 0.0, 3.6);

    qDebug() << "Meals as variant list:";
    const QVariantList tMeals = tService.mealsAsVariantList();
    for(const QVariant& tMeal : tMeals)
    {
        qDebug() << tMeal.toMap();
    }

    qDebug() << "Daily totals:";
    qDebug() << "Calories:" << tService.totalCalories();
    qDebug() << "Protein :" << tService.totalProtein();
    qDebug() << "Carbs   :" << tService.totalCarbs();
    qDebug() << "Fat     :" << tService.totalFat();

    // 5) Reload test
    NutritionService tReloadedService(&tDatabaseManager);
    qDebug() << "Reloaded meals:";
    const QVariantList tReloadedMeals = tReloadedService.mealsAsVariantList();
    for(const QVariant& tMeal : tReloadedMeals)
    {
        qDebug() << tMeal.toMap();
    }

    qDebug() << "Reloaded totals:";
    qDebug() << "Calories:" << tReloadedService.totalCalories();
    qDebug() << "Protein :" << tReloadedService.totalProtein();
    qDebug() << "Carbs   :" << tReloadedService.totalCarbs();
    qDebug() << "Fat     :" << tReloadedService.totalFat();

    qDebug() << "================ SERVICE TEST END =================";
}

static void runNutritionViewModelTests()
{
    qDebug() << "================ VIEWMODEL TEST START ================";

    DatabaseManager tDatabaseManager;
    NutritionService tService(&tDatabaseManager);
    NutritionViewModel tViewModel(&tService);

    const bool tAdded1 = tViewModel.addCatalogFood("Oatmeal", 68.0, 2.4, 12.0, 1.4);
    const bool tAdded2 = tViewModel.addCatalogFood("Egg", 155.0, 13.0, 1.1, 11.0);

    qDebug() << "VM addCatalogFood Oatmeal:" << tAdded1;
    qDebug() << "VM addCatalogFood Egg:" << tAdded2;

    const QVariantList tCatalogFoods = tViewModel.searchCatalogFoods("ea");
    qDebug() << "VM searchCatalogFoods('ea') count:" << tCatalogFoods.size();
    for(const QVariant& tItem : tCatalogFoods)
    {
        qDebug() << "VM catalog item:" << tItem.toMap();
    }

    tViewModel.addMeal("Breakfast");
    tViewModel.addMeal("Dinner");

    tViewModel.addFood(0, "Egg", 155.0, 13.0, 1.1, 11.0);
    tViewModel.addFood(1, "Oatmeal", 68.0, 2.4, 12.0, 1.4);

    qDebug() << "VM meals:";
    const QVariantList tMeals = tViewModel.getMeals();
    for(const QVariant& tMeal : tMeals)
    {
        qDebug() << tMeal.toMap();
    }

    qDebug() << "VM totals:";
    qDebug() << "Calories:" << tViewModel.getTotalCalories();
    qDebug() << "Protein :" << tViewModel.getTotalProtein();
    qDebug() << "Carbs   :" << tViewModel.getTotalCarbs();
    qDebug() << "Fat     :" << tViewModel.getTotalFat();

    qDebug() << "================ VIEWMODEL TEST END =================";
}

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");

    __android_log_print(ANDROID_LOG_ERROR, "HealthTrack", "MAIN EXECUTED");

    //Save NavigationManager enum type for qml for page indexing
    qmlRegisterUncreatableType<NavigationManager>(
        "HealthTrack", 1, 0,
        "NavigationManager",
        "NavigationManager is exposed via appController; this registration is for enum access only."
    );

    //App Controller(DB + Settings + ViewModels, for dev state give true, for release give false
    AppController tController;
    if(!tController.initialize(true))
    {
        __android_log_print(ANDROID_LOG_ERROR, "HealthTrack", "AppController initialization failed");
        return -1;
    }

    //Food insert and find test
    //testInsertFood();
    //runNutritionServiceTests();
    //runNutritionViewModelTests();

    //Application engine
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("appController", &tController);
    engine.loadFromModule("HealthTrack", "Main");

    if (engine.rootObjects().isEmpty())
    {
        __android_log_print(ANDROID_LOG_ERROR, "HealthTrack", "QML rootObjects is empty - load failed?");
        return -1;
    }

    return app.exec();
}
