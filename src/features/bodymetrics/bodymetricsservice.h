#ifndef BODYMETRICSSERVICE_H
#define BODYMETRICSSERVICE_H

#include <QObject>
#include <QDate>
#include <QVariantMap>

#include "bodymeasuremententry.h"
#include "bodycompositionmetrics.h"
#include "bodysegmentanalysis.h"
#include "segmentmetrics.h"
#include "bodymetricsrepository.h"

#include "../../core/databasemanager.h"

class BodyMetricsService final : public QObject
{
    Q_OBJECT

public:
    explicit BodyMetricsService(DatabaseManager* pDatabaseManager, QObject* pParent = nullptr);

    const BodyMeasurementEntry& measurementEntry() const noexcept;

    QDate getDate() const noexcept;
    void setDate(const QDate& pDate);

    const BodyCompositionMetrics& getComposition() const noexcept;
    void setComposition(const BodyCompositionMetrics& pComposition);

    const BodySegmentAnalysis& getSegmentAnalysis() const noexcept;
    void setSegmentAnalysis(const BodySegmentAnalysis& pSegmentAnalysis);

    void setWeightKg(double pWeightKg);
    void setMuscleMassKg(double pMuscleMassKg);
    void setMusclePecentage(double pMusclePercentage);
    void setFatMassKg(double pFatMassKg);
    void setFatPercentage(double pFatPercentage);
    void setLeanMassKg(double pLeanMassKg);
    void setBodyWaterMassKg(double pBodyWaterMassKg);
    void setBodyWaterPercentage(double pBodyWaterPercentage);
    void setBmi(double pBmi);
    void setBmr(double pBmr);

    void setTrunkMetrics(const SegmentMetrics& pMetrics);
    void setRightArmMetrics(const SegmentMetrics& pMetrics);
    void setLeftArmMetrics(const SegmentMetrics& pMetrics);
    void setRightLegMetrics(const SegmentMetrics& pMetrics);
    void setLeftLegMetrics(const SegmentMetrics& pMetrics);

    QVariantMap compositionAsVariantMap() const;
    QVariantMap segmentAnalysisAsVariantMap() const;
    QVariantMap measurementAsVariantMap() const;

    bool saveCurrentMeasurement();
    void loadCurrentMeasurement();
    bool deleteCurrentMeasurement();

signals:
    void dateChanged();
    void compositionChanged();
    void segmentAnalysisChanged();
    void measurementChanged();

private:
    static QVariantMap segmentToVariant(const SegmentMetrics& pMetrics);

    DatabaseManager* mDatabaseManager = nullptr;
    BodyMetricsRepository mRepository;
    BodyMeasurementEntry mMeasurement;
};

#endif // BODYMETRICSSERVICE_H
