#include "nutritionviewmodel.h"

NutritionViewModel::NutritionViewModel(NutritionService* pService, QObject *pParent)
    : QObject(pParent)
    , mService(pService)
{
    Q_ASSERT(mService);
    wireSignals();
}

QDate NutritionViewModel::getDate() const
{
    return mService->getDate();
}

void NutritionViewModel::setDate(const QDate &pDate)
{
    mService->setDate(pDate);
}

QVariantList NutritionViewModel::getMeals() const
{
    return mService->mealsAsVariantList();
}

QString NutritionViewModel::getDailyNotes() const
{
    return mService->getNotes();
}

void NutritionViewModel::setDailyNotes(const QString& pNotes)
{
    mService->setNotes(pNotes);
}

double NutritionViewModel::getTotalCalories() const
{
    return mService->totalCalories();
}

double NutritionViewModel::getTotalProtein() const
{
    return mService->totalProtein();
}

double NutritionViewModel::getTotalCarbs() const
{
    return mService->totalCarbs();
}

double NutritionViewModel::getTotalFat() const
{
    return mService->totalFat();
}

void NutritionViewModel::addMeal(const QString &pMealName)
{
    mService->addMeal(pMealName);
}

void NutritionViewModel::removeMeal(int pMealIndex)
{
    mService->removeMeal(pMealIndex);
}

void NutritionViewModel::clearMeals()
{
    mService->clearMeals();
}

void NutritionViewModel::addFoodToMeal(int pMealIndex, const QString &pName, double pCalories, double pProtein, double pCarbs, double pFat)
{
    mService->addFood(pMealIndex, pName, pCalories, pProtein, pCarbs, pFat);
}

void NutritionViewModel::removeFood(int pMealIndex, int pFoodIndex)
{
    mService->removeFood(pMealIndex, pFoodIndex);
}

void NutritionViewModel::clearFoods(int pMealIndex)
{
    mService->clearFoods(pMealIndex);
}

bool NutritionViewModel::addCatalogFood(const QString &pName, double pCalories, double pProtein, double pCarbs, double pFat)
{
    return mService->addCatalogFood(pName, pCalories, pProtein, pCarbs, pFat);
}

QVariantList NutritionViewModel::searchCatalogFoods(const QString &pSearchText) const
{
    return mService->searchCatalogFoods(pSearchText);
}

bool NutritionViewModel::saveCurrentDay()
{
    return mService->saveCurrentDay();
}

void NutritionViewModel::wireSignals()
{
    connect(mService, &NutritionService::dateChanged, this, &NutritionViewModel::dateChanged);
    connect(mService, &NutritionService::mealsChanged, this, &NutritionViewModel::mealsChanged);
    connect(mService, &NutritionService::notesChanged, this, &NutritionViewModel::dailyNotesChanged);

    connect(mService, &NutritionService::totalsChanged, this, &NutritionViewModel::totalCaloriesChanged);
    connect(mService, &NutritionService::totalsChanged, this, &NutritionViewModel::totalProteinChanged);
    connect(mService, &NutritionService::totalsChanged, this, &NutritionViewModel::totalCarbsChanged);
    connect(mService, &NutritionService::totalsChanged, this, &NutritionViewModel::totalFatChanged);

    connect(mService, &NutritionService::catalogFoodsChanged, this, &NutritionViewModel::catalogFoodsChanged);
}
