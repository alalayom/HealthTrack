#include "mealentry.h"

MealEntry::MealEntry()
{

}

MealEntry::MealEntry(QString pMealName)
    : mMealName(std::move(pMealName))
{

}

MealEntry::~MealEntry() = default;

const QString &MealEntry::getMealName() const noexcept
{
    return mMealName;
}

const QList<FoodEntry> &MealEntry::getFoods() const noexcept
{
    return mFoods;
}

void MealEntry::setMealName(QString pMealName)
{
    mMealName = std::move(pMealName);
}

void MealEntry::addFood(FoodEntry pFood)
{
    mFoods.append(std::move(pFood));
}

void MealEntry::removeFood(int pIndex)
{
    if(pIndex >= 0 && pIndex < mFoods.size())
    {
        mFoods.removeAt(pIndex);
    }
}

void MealEntry::clearFoods() noexcept
{
    mFoods.clear();
}

double MealEntry::totalCalories() const noexcept
{
    double tSum = 0.0;
    for(const auto& tFood : mFoods)
    {
        tSum += tFood.getCalories();
    }

    return tSum;
}

double MealEntry::totalProtein() const noexcept
{
    double tSum = 0.0;
    for(const auto& tFood : mFoods)
    {
        tSum += tFood.getProtein();
    }

    return tSum;
}

double MealEntry::totalCarbs() const noexcept
{
    double tSum = 0.0;
    for(const auto& tFood : mFoods)
    {
        tSum += tFood.getCarbs();
    }

    return tSum;
}

double MealEntry::totalFat() const noexcept
{
    double tSum = 0.0;
    for(const auto& tFood : mFoods)
    {
        tSum += tFood.getFat();
    }

    return tSum;
}
