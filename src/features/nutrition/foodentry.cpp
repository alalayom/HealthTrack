#include "foodentry.h"

FoodEntry::FoodEntry()
    : mCalories(0.0)
    , mProtein(0.0)
    , mCarbs(0.0)
    , mFat(0.0)
    , mGrams(0.0)
    , mCatalogFoodId(-1)
{

}

FoodEntry::FoodEntry(QString pName,
                     double pCalories,
                     double pProtein,
                     double pCarbs,
                     double pFat,
                     double pGrams,
                     int pCatalogFoodId)
    : mName(std::move(pName))
    , mCalories(0.0)
    , mProtein(0.0)
    , mCarbs(0.0)
    , mFat(0.0)
    , mGrams(0.0)
    , mCatalogFoodId(-1)
{
    setCalories(pCalories);
    setProtein(pProtein);
    setCarbs(pCarbs);
    setFat(pFat);
    setGrams(pGrams);
    setCatalogFoodId(pCatalogFoodId);
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

double FoodEntry::getGrams() const noexcept
{
    return mGrams;
}

int FoodEntry::getCatalogFoodId() const noexcept
{
    return mCatalogFoodId;
}

bool FoodEntry::hasCatalogFoodId() const noexcept
{
    return mCatalogFoodId > 0;
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

void FoodEntry::setGrams(double pGrams)
{
    mGrams = qMax(0.0, pGrams);
}

void FoodEntry::setCatalogFoodId(int pCatalogFoodId)
{
    mCatalogFoodId = pCatalogFoodId > 0 ? pCatalogFoodId : -1;
}


