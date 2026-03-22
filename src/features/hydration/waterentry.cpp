#include "waterentry.h"

WaterEntry::WaterEntry()
    : mDate(QDate::currentDate())
    , mAmountMl(0)
{

}

WaterEntry::WaterEntry(QDate pDate)
    : mDate(pDate)
    , mAmountMl(0)
{

}

WaterEntry::~WaterEntry() = default;

const QDate &WaterEntry::getDate() const noexcept
{
    return mDate;
}

int WaterEntry::getAmountMl() const noexcept
{
    return mAmountMl;
}

void WaterEntry::setDate(QDate pDate)
{
    mDate = pDate;
}

void WaterEntry::setAmountMl(int pAmountMl)
{
    if(pAmountMl < 0)
    {
        return;
    }

    mAmountMl = pAmountMl;
}

void WaterEntry::addWater(int pAmountMl)
{
    if(pAmountMl <= 0)
    {
        return;
    }

    mAmountMl += pAmountMl;
}

void WaterEntry::removeWater(int pAmountMl)
{
    if(pAmountMl <= 0)
    {
        return;
    }

    mAmountMl -= pAmountMl;

    if(mAmountMl < 0)
    {
        mAmountMl = 0;
    }
}

void WaterEntry::reset() noexcept
{
    mAmountMl = 0;
}
