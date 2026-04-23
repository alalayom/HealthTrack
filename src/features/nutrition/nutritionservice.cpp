#include "nutritionservice.h"

NutritionService::NutritionService(DatabaseManager* pDatabaseManager, QObject *pParent)
    : QObject(pParent)
    , mDatabaseManager(pDatabaseManager)
    , mRepository(pDatabaseManager)
    , mDaily(QDate::currentDate())
{
    ensureDefaultMeals();
}

const DailyEntry &NutritionService::dailyEntry() const noexcept
{
    return mDaily;
}

QDate NutritionService::getDate() const noexcept
{
    return mDaily.getDate();
}

void NutritionService::setDate(const QDate &pDate)
{
    if(mDaily.getDate() == pDate)
    {
        return;
    }

    mDaily = mRepository.loadDailyEntry(pDate);
    ensureDefaultMeals();

    emit dateChanged();
    emit notesChanged();
    emit mealsChanged();
    emit totalsChanged();
}

const QString &NutritionService::getNotes() const noexcept
{
    return mDaily.getNotes();
}

void NutritionService::setNotes(const QString &pNotes)
{
    if(mDaily.getNotes() == pNotes)
    {
        return;
    }

    mDaily.setNotes(pNotes);

    emit notesChanged();
}

void NutritionService::clearNotes()
{
    if(mDaily.getNotes().isEmpty())
    {
        return;
    }

    mDaily.clearNotes();
    saveCurrentDay();

    emit notesChanged();
}

int NutritionService::mealCount() const noexcept
{
    return mDaily.getMeals().size();
}

MealEntry NutritionService::mealAt(int pMealIndex) const
{
    const auto& tMeals = mDaily.getMeals();
    if(pMealIndex < 0 || pMealIndex >= tMeals.size())
    {
        return MealEntry{};
    }

    return tMeals.at(pMealIndex);
}

const QList<MealEntry> &NutritionService::getMeals() const noexcept
{
    return mDaily.getMeals();
}

void NutritionService::addMeal(const QString &pMealName)
{
    if(pMealName.trimmed().isEmpty())
    {
        return;
    }

    mDaily.addMeal(MealEntry(pMealName));
    saveCurrentDay();

    emit mealsChanged();
    emit totalsChanged();
}

void NutritionService::removeMeal(int pMealIndex)
{
    const int tMealSize = mDaily.getMeals().size();
    if(pMealIndex < 0 || pMealIndex >= tMealSize)
    {
        return;
    }

    mDaily.removeMeal(pMealIndex);
    saveCurrentDay();

    emit mealsChanged();
    emit totalsChanged();
}

void NutritionService::clearMeals() noexcept
{
    if(mDaily.getMeals().isEmpty())
    {
        return;
    }

    mDaily.clearMeals();
    saveCurrentDay();

    emit mealsChanged();
    emit totalsChanged();
}

void NutritionService::addFood(int pMealIndex,
                               const QString &pName,
                               double pCalories,
                               double pProtein,
                               double pCarbs,
                               double pFat,
                               double pGrams,
                               int pCatalogFoodId)
{
    addFood(pMealIndex, FoodEntry(pName, pCalories, pProtein, pCarbs, pFat, pGrams, pCatalogFoodId));
}

void NutritionService::addFood(int pMealIndex, FoodEntry pFood)
{
    if(pMealIndex < 0 || pMealIndex >= mDaily.getMeals().size())
    {
        return;
    }

    const QString tTrimmedName = pFood.getName().trimmed();
    if(tTrimmedName.isEmpty())
    {
        return;
    }

    if(pFood.getGrams() <= 0.0)
    {
        return;
    }

    pFood.setName(tTrimmedName);

    mDaily.mealRef(pMealIndex).addFood(std::move(pFood));
    saveCurrentDay();

    emit mealsChanged();
    emit totalsChanged();
}

void NutritionService::removeFood(int pMealIndex, int pFoodIndex)
{
    if(pMealIndex < 0 || pMealIndex >= mDaily.getMeals().size())
    {
        return;
    }

    auto& tMeal = mDaily.mealRef(pMealIndex);
    if(pFoodIndex < 0 || pFoodIndex >= tMeal.getFoods().size())
    {
        return;
    }

    tMeal.removeFood(pFoodIndex);
    saveCurrentDay();

    emit mealsChanged();
    emit totalsChanged();
}

void NutritionService::clearFoods(int pMealIndex)
{
    if(pMealIndex < 0 || pMealIndex >= mDaily.getMeals().size())
    {
        return;
    }

    auto& tMeal = mDaily.mealRef(pMealIndex);
    if(tMeal.getFoods().isEmpty())
    {
        return;
    }

    tMeal.clearFoods();
    saveCurrentDay();

    emit mealsChanged();
    emit totalsChanged();
}

double NutritionService::totalCalories() const noexcept
{
    return mDaily.totalCalories();
}

double NutritionService::totalProtein() const noexcept
{
    return mDaily.totalProtein();
}

double NutritionService::totalCarbs() const noexcept
{
    return mDaily.totalCarbs();
}

double NutritionService::totalFat() const noexcept
{
    return mDaily.totalFat();
}

QVariantList NutritionService::mealsAsVariantList() const
{
    QVariantList tList;
    const auto& tMeals = mDaily.getMeals();
    tList.reserve(tMeals.size());

    for(const auto& tMeal : tMeals)
    {
        tList.push_back(mealToVariant(tMeal));
    }

    return tList;
}

QVariantMap NutritionService::dailyTotalAsVariantMap() const
{
    QVariantMap tMap;
    tMap["calories"] = totalCalories();
    tMap["protein"] = totalProtein();
    tMap["carbs"] = totalCarbs();
    tMap["fat"] = totalFat();

    return tMap;
}

bool NutritionService::addCatalogFood(const QString &pName, double pCalories, double pProtein, double pCarbs, double pFat)
{
    const QString tTrimmedName = pName.trimmed();

    if(tTrimmedName.isEmpty())
    {
        return false;
    }

    const bool tSuccess = mRepository.insertCatalogFood(FoodEntry(tTrimmedName, pCalories, pProtein, pCarbs, pFat));

    if(tSuccess)
    {
        emit catalogFoodsChanged();
    }

    return tSuccess;
}

QVariantList NutritionService::searchCatalogFoods(const QString &pSearchText) const
{
    return mRepository.searchCatalogFoods(pSearchText);
}

bool NutritionService::saveCurrentDay()
{
    return mRepository.saveDailyEntry(mDaily);
}

void NutritionService::loadCurrentDay()
{
    mDaily = mRepository.loadDailyEntry(mDaily.getDate());
}

QVariantMap NutritionService::foodToVariant(const FoodEntry &pFood)
{
    QVariantMap tMap;
    tMap["name"] = pFood.getName();
    tMap["grams"] = pFood.getGrams();
    tMap["catalogFoodId"] = pFood.hasCatalogFoodId()
                                ? QVariant(pFood.getCatalogFoodId())
                                : QVariant();
    tMap["calories"] = pFood.getCalories();
    tMap["protein"] = pFood.getProtein();
    tMap["carbs"] = pFood.getCarbs();
    tMap["fat"] = pFood.getFat();

    return tMap;
}

QVariantMap NutritionService::mealToVariant(const MealEntry &pMeal)
{
    QVariantMap tMap;
    tMap["mealName"] = pMeal.getMealName();

    QVariantList tFoods;
    tFoods.reserve(pMeal.getFoods().size());

    for(const auto& tFood : pMeal.getFoods())
    {
        tFoods.push_back(foodToVariant(tFood));
    }

    tMap["foods"] = tFoods;

    QVariantMap tTotals;
    tTotals["calories"] = pMeal.totalCalories();
    tTotals["protein"] = pMeal.totalProtein();
    tTotals["carbs"] = pMeal.totalCarbs();
    tTotals["fat"] = pMeal.totalFat();

    tMap["totals"] = tTotals;

    return tMap;
}

void NutritionService::ensureDefaultMeals()
{
    if(!mDaily.getMeals().isEmpty())
    {
        return;
    }

    mDaily.addMeal(MealEntry("Breakfast"));
    mDaily.addMeal(MealEntry("Lunch"));
    mDaily.addMeal(MealEntry("Dinner"));
    mDaily.addMeal(MealEntry("Snack"));

    saveCurrentDay();
}
