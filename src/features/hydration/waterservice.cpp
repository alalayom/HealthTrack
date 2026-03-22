#include "waterservice.h"

#include <QtGlobal>

WaterService::WaterService(DatabaseManager *pDatabaseManager, QObject *pParent)
    : QObject(pParent)
    , mDatabaseManager(pDatabaseManager)
    , mRepository(pDatabaseManager)
    , mWater(QDate::currentDate())
{
    loadCurrentDay();
}

const WaterEntry &WaterService::waterEntry() const noexcept
{
    return mWater;
}

QDate WaterService::getDate() const noexcept
{
    return mWater.getDate();
}

void WaterService::setDate(const QDate &pDate)
{
    if(mWater.getDate() == pDate)
    {
        return;
    }

    mWater = mRepository.loadWaterEntry(pDate);

    emit dateChanged();
    emit waterChanged();
}

int WaterService::getCurrentAmountMl() const noexcept
{
    return mWater.getAmountMl();
}

int WaterService::getGoalAmountMl() const noexcept
{
    return mGoalAmountMl;
}

void WaterService::setGoalAmountMl(int pGoalAmountMl)
{
    if(pGoalAmountMl < 0)
    {
        return;
    }

    if(mGoalAmountMl == pGoalAmountMl)
    {
        return;
    }

    mGoalAmountMl = pGoalAmountMl;

    emit goalChanged();
    emit waterChanged();
}

int WaterService::getRemainingAmountMl() const noexcept
{
    const int tRemaining = mGoalAmountMl - mWater.getAmountMl();
    return qMax(0, tRemaining);
}

double WaterService::progress() const noexcept
{
    if(mGoalAmountMl <= 0)
    {
        return 0.0;
    }

    return static_cast<double>(mWater.getAmountMl()) / static_cast<double>(mGoalAmountMl);
}

void WaterService::addWater(int pAmountMl)
{
    if(pAmountMl <= 0)
    {
        return;
    }

    mWater.addWater(pAmountMl);
    saveCurrentDay();

    emit waterChanged();
}

void WaterService::removeWater(int pAmountMl)
{
    if(pAmountMl <= 0)
    {
        return;
    }

    mWater.removeWater(pAmountMl);
    saveCurrentDay();

    emit waterChanged();
}

void WaterService::setWaterAmount(int pAmountMl)
{
    if(pAmountMl < 0)
    {
        return;
    }

    if(mWater.getAmountMl() == pAmountMl)
    {
        return;
    }

    mWater.setAmountMl(pAmountMl);
    saveCurrentDay();

    emit waterChanged();
}

void WaterService::resetWater() noexcept
{
    if(mWater.getAmountMl() == 0)
    {
        return;
    }

    mWater.reset();
    saveCurrentDay();

    emit waterChanged();
}

bool WaterService::saveCurrentDay()
{
    return mRepository.saveWaterEntry(mWater);
}

void WaterService::loadCurrentDay()
{
    mWater = mRepository.loadWaterEntry(mWater.getDate());
}
