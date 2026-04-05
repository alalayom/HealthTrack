#ifndef BODYMETRICSVIEWMODEL_H
#define BODYMETRICSVIEWMODEL_H

#include <QObject>
#include <QDate>
#include <QVariantMap>

#include "bodymetricsservice.h"

class BodyMetricsViewModel final : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QDate date READ getDate WRITE setDate NOTIFY dateChanged FINAL)
    Q_PROPERTY(QVariantMap composition READ getComposition NOTIFY compositionChanged FINAL)
    Q_PROPERTY(QVariantMap segmentAnalysis READ getSegmentAnalysis NOTIFY segmentAnalysisChanged FINAL)

    Q_PROPERTY(double weightKg READ getWeightKg NOTIFY compositionChanged FINAL)

public:
    explicit BodyMetricsViewModel(BodyMetricsService* pService, QObject* pParent = nullptr);

    QDate getDate() const;
    void setDate(const QDate& pDate);

    QVariantMap getComposition() const;
    QVariantMap getSegmentAnalysis() const;

    double getWeightKg() const;

    Q_INVOKABLE void increaseWeightKg(double pStep = 0.1);
    Q_INVOKABLE void decreaseWeightKg(double pStep = 0.1);

    Q_INVOKABLE void setWeightKg(double pWeightKg);
    Q_INVOKABLE void setMuscleMassKg(double pMuscleMassKg);
    Q_INVOKABLE void setMusclePercentage(double pMusclePercentage);
    Q_INVOKABLE void setFatMassKg(double pFatMassKg);
    Q_INVOKABLE void setFatPercentage(double pFatPercentage);
    Q_INVOKABLE void setLeanMassKg(double pLeanMassKg);
    Q_INVOKABLE void setBodyWaterMassKg(double pBodyWaterMassKg);
    Q_INVOKABLE void setBodyWaterPercentage(double pBodyWaterPercentage);
    Q_INVOKABLE void setBmi(double pBmi);
    Q_INVOKABLE void setBmr(double pBmr);

    Q_INVOKABLE void setTrunkMetrics(double pMuscleMassKg, double pFatMassKg, double pFatPercentage, double pLeanMassKg);
    Q_INVOKABLE void setRightArmMetrics(double pMuscleMassKg, double pFatMassKg, double pFatPercentage, double pLeanMassKg);
    Q_INVOKABLE void setLeftArmMetrics(double pMuscleMassKg, double pFatMassKg, double pFatPercentage, double pLeanMassKg);
    Q_INVOKABLE void setRightLegMetrics(double pMuscleMassKg, double pFatMassKg, double pFatPercentage, double pLeanMassKg);
    Q_INVOKABLE void setLeftLegMetrics(double pMuscleMassKg, double pFatMassKg, double pFatPercentage, double pLeanMassKg);

    Q_INVOKABLE bool saveCurrentMeasurement();
    Q_INVOKABLE void loadCurrentMeasurement();
    Q_INVOKABLE bool deleteCurrentMeasurement();

signals:
    void dateChanged();
    void compositionChanged();
    void segmentAnalysisChanged();

private:
    void wireSignals();

    BodyMetricsService* mService = nullptr;
};

#endif // BODYMETRICSVIEWMODEL_H
