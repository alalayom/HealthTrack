#include "foodentry.h"

FoodEntry::FoodEntry()
    : mCalories(0.0)
    , mProtein(0.0)
    , mCarbs(0.0)
    , mFat(0.0)
{

}

FoodEntry::FoodEntry(QString pName, double pCalories, double pProtein, double pCarbs, double pFat)
    : mName(std::move(pName))
    , mCalories(0.0)
    , mProtein(0.0)
    , mCarbs(0.0)
    , mFat(0.0)
{
    setCalories(pCalories);
    setProtein(pProtein);
    setCarbs(pCarbs);
    setFat(pFat);
}

FoodEntry::~FoodEntry() = default;

const QString &FoodEntry::getName() const noexcept
{
    return mName;
}

double FoodEntry::getCalories() const noexcept
{
    return mCalories;
}

double FoodEntry::getProtein() const noexcept
{
    return mProtein;
}

double FoodEntry::getCarbs() const noexcept
{
    return mCarbs;
}

double FoodEntry::getFat() const noexcept
{
    return mFat;
}

void FoodEntry::setName(QString pName)
{
    mName = std::move(pName);
}

void FoodEntry::setCalories(double pCalories)
{
    mCalories = qMax(0.0, pCalories);
}

void FoodEntry::setProtein(double pProtein)
{
    mProtein = qMax(0.0, pProtein);
}

void FoodEntry::setCarbs(double pCarbs)
{
    mCarbs = qMax(0.0, pCarbs);
}

void FoodEntry::setFat(double pFat)
{
    mFat = qMax(0.0, pFat);
}


