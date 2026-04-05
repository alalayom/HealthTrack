#include "bodymetricsviewmodel.h"

#include "QtGlobal"

BodyMetricsViewModel::BodyMetricsViewModel(BodyMetricsService *pService, QObject *pParent)
    : QObject(pParent)
    , mService(pService)
{
    Q_ASSERT(mService);
    wireSignals();
}

QDate BodyMetricsViewModel::getDate() const
{
    return mService->getDate();
}

void BodyMetricsViewModel::setDate(const QDate& pDate)
{
    mService->setDate(pDate);
}

QVariantMap BodyMetricsViewModel::getComposition() const
{
    return mService->compositionAsVariantMap();
}

QVariantMap BodyMetricsViewModel::getSegmentAnalysis() const
{
    return mService->segmentAnalysisAsVariantMap();
}

void BodyMetricsViewModel::setWeightKg(double pWeightKg)
{
    mService->setWeightKg(pWeightKg);
}

void BodyMetricsViewModel::setMuscleMassKg(double pMuscleMassKg)
{
    mService->setMuscleMassKg(pMuscleMassKg);
}

void BodyMetricsViewModel::setMusclePercentage(double pMusclePercentage)
{
    mService->setMusclePercentage(pMusclePercentage);
}

void BodyMetricsViewModel::setFatMassKg(double pFatMassKg)
{
    mService->setFatMassKg(pFatMassKg);
}

void BodyMetricsViewModel::setFatPercentage(double pFatPercentage)
{
    mService->setFatPercentage(pFatPercentage);
}

void BodyMetricsViewModel::setLeanMassKg(double pLeanMassKg)
{
    mService->setLeanMassKg(pLeanMassKg);
}

void BodyMetricsViewModel::setBodyWaterMassKg(double pBodyWaterMassKg)
{
    mService->setBodyWaterMassKg(pBodyWaterMassKg);
}

void BodyMetricsViewModel::setBodyWaterPercentage(double pBodyWaterPercentage)
{
    mService->setBodyWaterPercentage(pBodyWaterPercentage);
}

void BodyMetricsViewModel::setBmi(double pBmi)
{
    mService->setBmi(pBmi);
}

void BodyMetricsViewModel::setBmr(double pBmr)
{
    mService->setBmr(pBmr);
}

void BodyMetricsViewModel::setTrunkMetrics(double pMuscleMassKg, double pFatMassKg, double pFatPercentage, double pLeanMassKg)
{
    mService->setTrunkMetrics(SegmentMetrics(pMuscleMassKg, pFatMassKg, pFatPercentage, pLeanMassKg));
}

void BodyMetricsViewModel::setRightArmMetrics(double pMuscleMassKg, double pFatMassKg, double pFatPercentage, double pLeanMassKg)
{
    mService->setRightArmMetrics(SegmentMetrics(pMuscleMassKg, pFatMassKg, pFatPercentage, pLeanMassKg));
}

void BodyMetricsViewModel::setLeftArmMetrics(double pMuscleMassKg, double pFatMassKg, double pFatPercentage, double pLeanMassKg)
{
    mService->setLeftArmMetrics(SegmentMetrics(pMuscleMassKg, pFatMassKg, pFatPercentage, pLeanMassKg));
}

void BodyMetricsViewModel::setRightLegMetrics(double pMuscleMassKg, double pFatMassKg, double pFatPercentage, double pLeanMassKg)
{
    mService->setRightLegMetrics(SegmentMetrics(pMuscleMassKg, pFatMassKg, pFatPercentage, pLeanMassKg));
}

void BodyMetricsViewModel::setLeftLegMetrics(double pMuscleMassKg, double pFatMassKg, double pFatPercentage, double pLeanMassKg)
{
    mService->setLeftLegMetrics(SegmentMetrics(pMuscleMassKg, pFatMassKg, pFatPercentage, pLeanMassKg));
}

bool BodyMetricsViewModel::saveCurrentMeasurement()
{
    return mService->saveCurrentMeasurement();
}

void BodyMetricsViewModel::loadCurrentMeasurement()
{
    mService->loadCurrentMeasurement();
}

bool BodyMetricsViewModel::deleteCurrentMeasurement()
{
    return mService->deleteCurrentMeasurement();
}

void BodyMetricsViewModel::wireSignals()
{
    connect(mService, &BodyMetricsService::dateChanged, this, &BodyMetricsViewModel::dateChanged);
    connect(mService, &BodyMetricsService::compositionChanged, this, &BodyMetricsViewModel::compositionChanged);
    connect(mService, &BodyMetricsService::segmentAnalysisChanged, this, &BodyMetricsViewModel::segmentAnalysisChanged);
}

double BodyMetricsViewModel::getWeightKg() const
{
    return mService->getComposition().getWeightKg();
}

void BodyMetricsViewModel::increaseWeightKg(double pStep)
{
    const double tCurrentWeight = getWeightKg();
    setWeightKg(tCurrentWeight + pStep);
}

void BodyMetricsViewModel::decreaseWeightKg(double pStep)
{
    const double tCurrentWeight = getWeightKg();
    const double tNewWeight = qMax(0.0, tCurrentWeight - pStep);
    setWeightKg(tNewWeight);
}
