#include "waterviewmodel.h"

WaterViewModel::WaterViewModel(WaterService *pWaterService, QObject *pParent)
    : QObject(pParent)
    , mService(pWaterService)
{
    Q_ASSERT(mService);
    wireSignals();
}

QDate WaterViewModel::getDate() const
{
    return mService->getDate();
}

void WaterViewModel::setDate(const QDate& pDate)
{
    mService->setDate(pDate);
}

int WaterViewModel::getCurrentAmountMl() const
{
    return mService->getCurrentAmountMl();
}

int WaterViewModel::getGoalAmountMl() const
{
    return mService->getGoalAmountMl();
}

void WaterViewModel::setGoalAmountMl(int pGoalAmountMl)
{
    mService->setGoalAmountMl(pGoalAmountMl);
}

int WaterViewModel::getRemainingAmountMl() const
{
    return mService->getRemainingAmountMl();
}

double WaterViewModel::getProgress() const
{
    return mService->progress();
}

int WaterViewModel::getSelectedCupAmountMl() const
{
    return mSelectedCupAmountMl;
}

void WaterViewModel::setSelectedCupAmountMl(int pSelectedCupAmountMl)
{
    if(pSelectedCupAmountMl <= 0)
    {
        return;
    }

    if(mSelectedCupAmountMl == pSelectedCupAmountMl)
    {
        return;
    }

    mSelectedCupAmountMl = pSelectedCupAmountMl;

    emit selectedCupAmountMlChanged();
    emit filledCupCountChanged();
    emit targetCupCountChanged();
}

int WaterViewModel::getFilledCupCount() const
{
    if(mSelectedCupAmountMl <= 0)
    {
        return 0;
    }

    return getCurrentAmountMl() / mSelectedCupAmountMl;
}

int WaterViewModel::getTargetCupCount() const
{
    if(mSelectedCupAmountMl <= 0)
    {
        return 0;
    }

    const int tGoalAmountMl = getGoalAmountMl();
    return (tGoalAmountMl + mSelectedCupAmountMl - 1) / mSelectedCupAmountMl;
}

void WaterViewModel::addWater(int pAmountMl)
{
    mService->addWater(pAmountMl);
}

void WaterViewModel::removeWater(int pAmountMl)
{
    mService->removeWater(pAmountMl);
}

void WaterViewModel::setWaterAmount(int pAmountMl)
{
    mService->setWaterAmount(pAmountMl);
}

void WaterViewModel::resetWater()
{
    mService->resetWater();
}

void WaterViewModel::addSelectedCup()
{
    mService->addWater(mSelectedCupAmountMl);
}

void WaterViewModel::removeSelectedCup()
{
    mService->removeWater(mSelectedCupAmountMl);
}

void WaterViewModel::toggleCup(int pCupIndex)
{
    if(pCupIndex < 0 || mSelectedCupAmountMl <= 0)
    {
        return;
    }

    const int tFilledCupCount = getFilledCupCount();
    int tNewCupCount = 0;

    if(pCupIndex < tFilledCupCount)
    {
        tNewCupCount = pCupIndex;
    }
    else
    {
        tNewCupCount = pCupIndex + 1;
    }

    mService->setWaterAmount(tNewCupCount * mSelectedCupAmountMl);
}

void WaterViewModel::wireSignals()
{
    connect(mService, &WaterService::dateChanged, this, &WaterViewModel::dateChanged);
    connect(mService, &WaterService::waterChanged, this, &WaterViewModel::currentAmountMlChanged);
    connect(mService, &WaterService::waterChanged, this, &WaterViewModel::remainingAmountMlChanged);
    connect(mService, &WaterService::waterChanged, this, &WaterViewModel::progressChanged);
    connect(mService, &WaterService::waterChanged, this, &WaterViewModel::filledCupCountChanged);
    connect(mService, &WaterService::goalChanged, this, &WaterViewModel::goalAmountMlChanged);
    connect(mService, &WaterService::goalChanged, this, &WaterViewModel::remainingAmountMlChanged);
    connect(mService, &WaterService::goalChanged, this, &WaterViewModel::progressChanged);
    connect(mService, &WaterService::goalChanged, this, &WaterViewModel::targetCupCountChanged);
}
