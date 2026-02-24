#include "nutritionrepository.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

NutritionRepository::NutritionRepository(DatabaseManager* pDatabaseManager)
    : mDatabaseManager(pDatabaseManager)
{

}

bool NutritionRepository::saveDailyEntry(const DailyEntry& pEntry)
{
    if(!mDatabaseManager->database().transaction())
    {
        return false;
    }

    int tDailyId = ensureDailyId(pEntry.getDate());
    if(tDailyId <= 0)
    {
        mDatabaseManager->database().rollback();
        return false;
    }

    //Delete old meals and foods
    QSqlQuery tDeleteMeals(mDatabaseManager->database());
    tDeleteMeals.prepare("DELETE FROM meal_entries WHERE daily_id = ?");
    tDeleteMeals.addBindValue(tDailyId);

    if(!tDeleteMeals.exec())
    {
        mDatabaseManager->database().rollback();
        return false;
    }

    //Insert meals and foods
    for(const auto& tMeal : pEntry.getMeals())
    {
        int tMealId = insertMeal(tDailyId, tMeal);
        if(tMealId <= 0)
        {
            mDatabaseManager->database().rollback();
            return false;
        }

        for(const auto& tFood : tMeal.getFoods())
        {
            if(!insertFood(tMealId, tFood))
            {
                mDatabaseManager->database().rollback();
                return false;
            }
        }
    }

    return mDatabaseManager->database().commit();
}

DailyEntry NutritionRepository::loadDailyEntry(const QDate& pDate)
{
    DailyEntry tEntry(pDate);
    QSqlQuery tDailyQuery(mDatabaseManager->database());
    tDailyQuery.prepare("SELECT id FROM daily_entries WHERE date = ?");
    tDailyQuery.addBindValue(pDate.toString(Qt::ISODate));

    if(!tDailyQuery.exec() || !tDailyQuery.next())
    {
        return tEntry;
    }

    int tDailyId = tDailyQuery.value(0).toInt();
    QSqlQuery tMealQuery(mDatabaseManager->database());
    tMealQuery.prepare("SELECT id, name FROM meal_entries WHERE daily_id = ?");
    tMealQuery.addBindValue(tDailyId);

    if(!tMealQuery.exec())
    {
        return tEntry;
    }

    while(tMealQuery.next())
    {
        int tMealId = tMealQuery.value(0).toInt();
        QString tMealName = tMealQuery.value(1).toString();
        MealEntry tMeal(tMealName);

        QSqlQuery tFoodQuery(mDatabaseManager->database());
        tFoodQuery.prepare("SELECT name, calories, protein, carbs, fat FROM food_entries WHERE meal_id = ?");
        tFoodQuery.addBindValue(tMealId);

        if(tFoodQuery.exec())
        {
            while(tFoodQuery.next())
            {
                tMeal.addFood(FoodEntry(
                    tFoodQuery.value(0).toString(),
                    tFoodQuery.value(1).toDouble(),
                    tFoodQuery.value(2).toDouble(),
                    tFoodQuery.value(3).toDouble(),
                    tFoodQuery.value(4).toDouble()
                ));
            }
        }

        tEntry.addMeal(tMeal);
    }

    return tEntry;
}

bool NutritionRepository::deleteDailyEntry(const QDate& pDate)
{
    QSqlQuery tQuery(mDatabaseManager->database());
    tQuery.prepare("DELETE FROM daily_entries WHERE date = ?");
    tQuery.addBindValue(pDate.toString(Qt::ISODate));
    return tQuery.exec();
}

int NutritionRepository::ensureDailyId(const QDate& pDate)
{
    QSqlQuery tQuery(mDatabaseManager->database());
    tQuery.prepare("SELECT id FROM daily_entries WHERE date = ?");
    tQuery.addBindValue(pDate.toString(Qt::ISODate));

    if(tQuery.exec() && tQuery.next())
    {
        return tQuery.value(0).toInt();
    }

    tQuery.prepare("INSERT INTO daily_entries(date) VALUES(?)");
    tQuery.addBindValue(pDate.toString(Qt::ISODate));

    if(!tQuery.exec())
    {
        return -1;
    }

    return tQuery.lastInsertId().toInt();
}

int NutritionRepository::insertMeal(int pDailyId, const MealEntry& pMeal)
{
    QSqlQuery tQuery(mDatabaseManager->database());
    tQuery.prepare("INSERT INTO meal_entries(daily_id, name) VALUES(?, ?)");
    tQuery.addBindValue(pDailyId);
    tQuery.addBindValue(pMeal.getMealName());

    if(!tQuery.exec())
    {
        return -1;
    }

    return tQuery.lastInsertId().toInt();
}

bool NutritionRepository::insertFood(int pMealId, const FoodEntry& pFood)
{
    QSqlQuery tQuery(mDatabaseManager->database());
    tQuery.prepare(R"(
        INSERT INTO food_entries(meal_id, name, calories, protein, carbs, fat)
        VALUES(?, ?, ?, ?, ?, ?)
    )");

    tQuery.addBindValue(pMealId);
    tQuery.addBindValue(pFood.getName());
    tQuery.addBindValue(pFood.getCalories());
    tQuery.addBindValue(pFood.getProtein());
    tQuery.addBindValue(pFood.getCarbs());
    tQuery.addBindValue(pFood.getFat());

    return tQuery.exec();
}
