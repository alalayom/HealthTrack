#include "dailyentry.h"

DailyEntry::DailyEntry()
    : mDate(QDate::currentDate())
{

}

DailyEntry::DailyEntry(QDate pDate)
    : mDate(std::move(pDate))
{

}

DailyEntry::~DailyEntry() = default;

const QDate &DailyEntry::getDate() const noexcept
{
    return mDate;
}

const QList<MealEntry> &DailyEntry::getMeals() const noexcept
{
    return mMeals;
}

void DailyEntry::setDate(QDate pDate)
{
    mDate = std::move(pDate);
}

void DailyEntry::addMeal(MealEntry pMeal)
{
    mMeals.append(std::move(pMeal));
}

void DailyEntry::removeMeal(int pIndex)
{
    if(pIndex >= 0 && pIndex < mMeals.size())
    {
        mMeals.removeAt(pIndex);
    }
}

void DailyEntry::clearMeals() noexcept
{
    mMeals.clear();
}

double DailyEntry::totalCalories() const noexcept
{
    double tSum = 0.0;
    for(const auto& tMeal : mMeals)
    {
        tSum += tMeal.totalCalories();
    }

    return tSum;
}

double DailyEntry::totalProtein() const noexcept
{
    double tSum = 0.0;
    for(const auto& tMeal : mMeals)
    {
        tSum += tMeal.totalProtein();
    }

    return tSum;
}

double DailyEntry::totalCarbs() const noexcept
{
    double tSum = 0.0;
    for(const auto& tMeal : mMeals)
    {
        tSum += tMeal.totalCarbs();
    }

    return tSum;
}

double DailyEntry::totalFat() const noexcept
{
    double tSum = 0.0;
    for(const auto& tMeal : mMeals)
    {
        tSum += tMeal.totalFat();
    }

    return tSum;
}

MealEntry &DailyEntry::mealRef(int pIndex)
{
    return mMeals[pIndex];
}

const MealEntry &DailyEntry::mealRef(int pIndex) const
{
    return mMeals[pIndex];
}
