#ifndef BODYMETRICSREPOSITORY_H
#define BODYMETRICSREPOSITORY_H

#include <QDate>

#include "bodymeasuremententry.h"
#include "../../core/databasemanager.h"

class BodyMetricsRepository final
{
public:
    explicit BodyMetricsRepository(DatabaseManager* pDatabaseManager);
    ~BodyMetricsRepository() = default;

    bool saveMeasurementEntry(const BodyMeasurementEntry& pEntry);
    BodyMeasurementEntry loadMeasurementEntry(const QDate& pDate);
    BodyMeasurementEntry loadLatestMeasurementEntryOnOrBefore(const QDate& pDate);
    bool deleteMeasurementEntry(const QDate& pDate);

private:
    int ensureMeasurementId(const QDate& pDate);
    bool saveCompositionMetrics(int pMeasurementId, const BodyCompositionMetrics& pComposition);
    bool saveSegmentMetrics(int pMeasurementId, const QString& pSegmentName, const SegmentMetrics& pMetrics);

    DatabaseManager* mDatabaseManager = nullptr;

};

#endif // BODYMETRICSREPOSITORY_H
