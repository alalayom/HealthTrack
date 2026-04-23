#include "bodymetricsservice.h"

BodyMetricsService::BodyMetricsService(DatabaseManager *pDatabaseManager, QObject *pParent)
    : QObject(pParent)
    , mDatabaseManager(pDatabaseManager)
    , mRepository(pDatabaseManager)
    , mMeasurement()
{
    mMeasurement.setMeasurementDate(QDate::currentDate());
}

const BodyMeasurementEntry &BodyMetricsService::measurementEntry() const noexcept
{
    return mMeasurement;
}

QDate BodyMetricsService::getDate() const noexcept
{
    return mMeasurement.getMeasurementDate();
}

void BodyMetricsService::setDate(const QDate &pDate)
{
    const bool tDateChanged = (mMeasurement.getMeasurementDate() != pDate);

    mMeasurement = mRepository.loadMeasurementEntry(pDate);

    if(mMeasurement.getId() <= 0)
    {
        BodyMeasurementEntry tFallbackMeasurement = mRepository.loadLatestMeasurementEntryOnOrBefore(pDate);
        if(tFallbackMeasurement.getId() > 0)
        {
            tFallbackMeasurement.setId(-1);
            mMeasurement = tFallbackMeasurement;
        }
    }

    if(mMeasurement.getMeasurementDate() != pDate)
    {
        mMeasurement.setMeasurementDate(pDate);
    }

    if(tDateChanged)
    {
        emit dateChanged();
    }

    emit compositionChanged();
    emit segmentAnalysisChanged();
    emit measurementChanged();
}

const BodyCompositionMetrics &BodyMetricsService::getComposition() const noexcept
{
    return mMeasurement.getComposition();
}

void BodyMetricsService::setComposition(const BodyCompositionMetrics &pComposition)
{
    mMeasurement.setComposition(pComposition);
    saveCurrentMeasurement();

    emit compositionChanged();
    emit measurementChanged();
}

const BodySegmentAnalysis &BodyMetricsService::getSegmentAnalysis() const noexcept
{
    return mMeasurement.getSegmentAnalysis();
}

void BodyMetricsService::setSegmentAnalysis(const BodySegmentAnalysis &pSegmentAnalysis)
{
    mMeasurement.setSegmentAnalysis(pSegmentAnalysis);
    saveCurrentMeasurement();

    emit segmentAnalysisChanged();
    emit measurementChanged();
}

void BodyMetricsService::setWeightKg(double pWeightKg)
{
    BodyCompositionMetrics tComposition = mMeasurement.getComposition();
    tComposition.setWeightKg(pWeightKg);
    mMeasurement.setComposition(tComposition);

    saveCurrentMeasurement();

    emit compositionChanged();
    emit measurementChanged();
}

void BodyMetricsService::setMuscleMassKg(double pMuscleMassKg)
{
    BodyCompositionMetrics tComposition = mMeasurement.getComposition();
    tComposition.setMuscleMassKg(pMuscleMassKg);
    mMeasurement.setComposition(tComposition);

    saveCurrentMeasurement();

    emit compositionChanged();
    emit measurementChanged();
}

void BodyMetricsService::setMusclePercentage(double pMusclePercentage)
{
    BodyCompositionMetrics tComposition = mMeasurement.getComposition();
    tComposition.setMusclePercentage(pMusclePercentage);
    mMeasurement.setComposition(tComposition);

    saveCurrentMeasurement();

    emit compositionChanged();
    emit measurementChanged();
}

void BodyMetricsService::setFatMassKg(double pFatMassKg)
{
    BodyCompositionMetrics tComposition = mMeasurement.getComposition();
    tComposition.setFatMassKg(pFatMassKg);
    mMeasurement.setComposition(tComposition);

    saveCurrentMeasurement();

    emit compositionChanged();
    emit measurementChanged();
}

void BodyMetricsService::setFatPercentage(double pFatPercentage)
{
    BodyCompositionMetrics tComposition = mMeasurement.getComposition();
    tComposition.setFatPercentage(pFatPercentage);
    mMeasurement.setComposition(tComposition);

    saveCurrentMeasurement();

    emit compositionChanged();
    emit measurementChanged();
}

void BodyMetricsService::setLeanMassKg(double pLeanMassKg)
{
    BodyCompositionMetrics tComposition = mMeasurement.getComposition();
    tComposition.setLeanMassKg(pLeanMassKg);
    mMeasurement.setComposition(tComposition);

    saveCurrentMeasurement();

    emit compositionChanged();
    emit measurementChanged();
}

void BodyMetricsService::setBodyWaterMassKg(double pBodyWaterMassKg)
{
    BodyCompositionMetrics tComposition = mMeasurement.getComposition();
    tComposition.setBodyWaterMassKg(pBodyWaterMassKg);
    mMeasurement.setComposition(tComposition);

    saveCurrentMeasurement();

    emit compositionChanged();
    emit measurementChanged();
}

void BodyMetricsService::setBodyWaterPercentage(double pBodyWaterPercentage)
{
    BodyCompositionMetrics tComposition = mMeasurement.getComposition();
    tComposition.setBodyWaterPercentage(pBodyWaterPercentage);
    mMeasurement.setComposition(tComposition);

    saveCurrentMeasurement();

    emit compositionChanged();
    emit measurementChanged();
}

void BodyMetricsService::setBmi(double pBmi)
{
    BodyCompositionMetrics tComposition = mMeasurement.getComposition();
    tComposition.setBmi(pBmi);
    mMeasurement.setComposition(tComposition);

    saveCurrentMeasurement();

    emit compositionChanged();
    emit measurementChanged();
}

void BodyMetricsService::setBmr(double pBmr)
{
    BodyCompositionMetrics tComposition = mMeasurement.getComposition();
    tComposition.setBmr(pBmr);
    mMeasurement.setComposition(tComposition);

    saveCurrentMeasurement();

    emit compositionChanged();
    emit measurementChanged();
}

void BodyMetricsService::setTrunkMetrics(const SegmentMetrics &pMetrics)
{
    BodySegmentAnalysis tAnalysis = mMeasurement.getSegmentAnalysis();
    tAnalysis.setTrunk(pMetrics);
    mMeasurement.setSegmentAnalysis(tAnalysis);

    saveCurrentMeasurement();

    emit segmentAnalysisChanged();
    emit measurementChanged();
}

void BodyMetricsService::setRightArmMetrics(const SegmentMetrics &pMetrics)
{
    BodySegmentAnalysis tAnalysis = mMeasurement.getSegmentAnalysis();
    tAnalysis.setRightArm(pMetrics);
    mMeasurement.setSegmentAnalysis(tAnalysis);

    saveCurrentMeasurement();

    emit segmentAnalysisChanged();
    emit measurementChanged();
}

void BodyMetricsService::setLeftArmMetrics(const SegmentMetrics &pMetrics)
{
    BodySegmentAnalysis tAnalysis = mMeasurement.getSegmentAnalysis();
    tAnalysis.setLeftArm(pMetrics);
    mMeasurement.setSegmentAnalysis(tAnalysis);

    saveCurrentMeasurement();

    emit segmentAnalysisChanged();
    emit measurementChanged();
}

void BodyMetricsService::setRightLegMetrics(const SegmentMetrics &pMetrics)
{
    BodySegmentAnalysis tAnalysis = mMeasurement.getSegmentAnalysis();
    tAnalysis.setRightLeg(pMetrics);
    mMeasurement.setSegmentAnalysis(tAnalysis);

    saveCurrentMeasurement();

    emit segmentAnalysisChanged();
    emit measurementChanged();
}

void BodyMetricsService::setLeftLegMetrics(const SegmentMetrics &pMetrics)
{
    BodySegmentAnalysis tAnalysis = mMeasurement.getSegmentAnalysis();
    tAnalysis.setLeftLeg(pMetrics);
    mMeasurement.setSegmentAnalysis(tAnalysis);

    saveCurrentMeasurement();

    emit segmentAnalysisChanged();
    emit measurementChanged();
}

QVariantMap BodyMetricsService::compositionAsVariantMap() const
{
    QVariantMap tMap;
    const auto& tComposition = mMeasurement.getComposition();

    tMap["weightKg"] = tComposition.getWeightKg();
    tMap["muscleMassKg"] = tComposition.getMuscleMassKg();
    tMap["musclePercentage"] = tComposition.getMusclePercentage();
    tMap["fatMassKg"] = tComposition.getFatMassKg();
    tMap["fatPercentage"] = tComposition.getFatPercentage();
    tMap["leanMassKg"] = tComposition.getLeanMassKg();
    tMap["bodyWaterMassKg"] = tComposition.getBodyWaterMassKg();
    tMap["bodyWaterPercentage"] = tComposition.getBodyWaterPercentage();
    tMap["bmi"] = tComposition.getBmi();
    tMap["bmr"] = tComposition.getBmr();

    return tMap;
}

QVariantMap BodyMetricsService::segmentAnalysisAsVariantMap() const
{
    QVariantMap tMap;
    const auto& tAnalysis = mMeasurement.getSegmentAnalysis();

    tMap["trunk"] = segmentToVariant(tAnalysis.getTrunk());
    tMap["rightArm"] = segmentToVariant(tAnalysis.getRightArm());
    tMap["leftArm"] = segmentToVariant(tAnalysis.getLeftArm());
    tMap["rightLeg"] = segmentToVariant(tAnalysis.getRightLeg());
    tMap["leftLeg"] = segmentToVariant(tAnalysis.getLeftLeg());

    return tMap;
}

QVariantMap BodyMetricsService::measurementAsVariantMap() const
{
    QVariantMap tMap;

    tMap["date"] = mMeasurement.getMeasurementDate().toString(Qt::ISODate);
    tMap["composition"] = compositionAsVariantMap();
    tMap["segmentAnalysis"] = segmentAnalysisAsVariantMap();

    return tMap;
}

bool BodyMetricsService::saveCurrentMeasurement()
{
    return mRepository.saveMeasurementEntry(mMeasurement);
}

void BodyMetricsService::loadCurrentMeasurement()
{
    const QDate tDate = mMeasurement.getMeasurementDate();
    mMeasurement = mRepository.loadMeasurementEntry(tDate);
    mMeasurement.setMeasurementDate(tDate);

    emit compositionChanged();
    emit segmentAnalysisChanged();
    emit measurementChanged();
}

bool BodyMetricsService::deleteCurrentMeasurement()
{
    const QDate tDate = mMeasurement.getMeasurementDate();
    const bool tSuccess = mRepository.deleteMeasurementEntry(tDate);

    if(tSuccess)
    {
        mMeasurement = BodyMeasurementEntry();
        mMeasurement.setMeasurementDate(tDate);

        emit dateChanged();
        emit compositionChanged();
        emit segmentAnalysisChanged();
        emit measurementChanged();
    }

    return tSuccess;
}

QVariantMap BodyMetricsService::segmentToVariant(const SegmentMetrics &pMetrics)
{
    QVariantMap tMap;

    tMap["muscleMassKg"] = pMetrics.getMuscleMassKg();
    tMap["fatMassKg"] = pMetrics.getFatMassKg();
    tMap["fatPercentage"] = pMetrics.getFatPercentage();
    tMap["leanMassKg"] = pMetrics.getLeanMassKg();

    return tMap;
}
