#include "nutritionservice.h"

NutritionService::NutritionService(QObject *pParent)

    : QObject(pParent)
    , mDaily(QDate::currentDate())
{

}

const DailyEntry &NutritionService::dailyEntry() const noexcept
{
    return mDaily;
}

QDate NutritionService::date() const noexcept
{
    return mDaily.getDate();
}

void NutritionService::setDate(const QDate &pDate)
{
    if(mDaily.getDate() == pDate)
    {
        return;
    }

    mDaily.setDate(pDate);
    emit dateChanged();

    //This could change meals and total
    emit mealsChanged();
    emit totalsChanged();
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
    emit mealsChanged();
    emit totalsChanged();
}

void NutritionService::addFood(int pMealIndex, const QString &pName, double pCalories, double pProtein, double pCarbs, double pFat)
{
    auto tMeals = mDaily.getMeals();
    if(pMealIndex < 0 || pMealIndex >= tMeals.size())
    {
        return;
    }

    const QString tTrimmedName = pName.trimmed();
    if(tTrimmedName.isEmpty())
    {
        return;
    }

    FoodEntry tFood(tTrimmedName, pCalories, pProtein, pCarbs, pFat);
    MealEntry tMeal = tMeals.at(pMealIndex);
    tMeal.addFood(std::move(tFood));

    mDaily.removeMeal(pMealIndex);
    tMeals.insert(pMealIndex, std::move(tMeal));

    mDaily.clearMeals();
    for(auto& tMealInstance : tMeals)
    {
        mDaily.addMeal(std::move(tMealInstance));
    }

    emit mealsChanged();
    emit totalsChanged();
}

void NutritionService::removeFood(int pMealIndex, int pFoodIndex)
{
    auto tMeals = mDaily.getMeals();
    if(pMealIndex < 0 || pMealIndex >= tMeals.size())
    {
        return;
    }

    MealEntry tMeal = tMeals.at(pMealIndex);
    const int tFoodCount = tMeal.getFoods().size();
    if(pFoodIndex < 0 || pFoodIndex >= tFoodCount)
    {
        return;
    }

    tMeal.removeFood(pFoodIndex);
    mDaily.removeMeal(pMealIndex);
    tMeals.insert(pMealIndex, std::move(tMeal));

    mDaily.clearMeals();
    for(auto& tMealInstance : tMeals)
    {
        mDaily.addMeal(std::move(tMealInstance));
    }

    emit mealsChanged();
    emit totalsChanged();
}

void NutritionService::clearFoods(int pMealIndex)
{
    auto tMeals = mDaily.getMeals();
    if(pMealIndex < 0 || pMealIndex >= tMeals.size())
    {
        return;
    }

    MealEntry tMeal = tMeals.at(pMealIndex);
    if(tMeal.getFoods().isEmpty())
    {
        return;
    }

    tMeal.clearFoods();

    mDaily.removeMeal(pMealIndex);
    tMeals.insert(pMealIndex, std::move(tMeal));
    mDaily.clearMeals();

    for(auto& tMealInstance : tMeals)
    {
        mDaily.addMeal(std::move(tMealInstance));
    }

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

QVariantMap NutritionService::foodToVariant(const FoodEntry &pFood)
{
    QVariantMap tMap;
    tMap["name"] = pFood.getName();
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
