#ifndef BODYMEASUREMENTENTRY_H
#define BODYMEASUREMENTENTRY_H

#include <QDate>
#include <QString>

#include "bodycompositionmetrics.h"
#include "bodysegmentanalysis.h"

class BodyMeasurementEntry
{
public:
    BodyMeasurementEntry();
    explicit BodyMeasurementEntry(int pId, QDate pMeasurementDate,
                                  BodyCompositionMetrics pComposition,
                                  BodySegmentAnalysis pSegmentAnalysis);

    ~BodyMeasurementEntry();

    int getId() const noexcept;
    void setId(int pId) noexcept;

    const QDate& getMeasurementDate() const noexcept;
    void setMeasurementDate(QDate pMeasurementDate);

    const BodyCompositionMetrics& getComposition() const noexcept;
    void setComposition(BodyCompositionMetrics pComposition);

    const BodySegmentAnalysis& getSegmentAnalysis() const noexcept;
    void setSegmentAnalysis(BodySegmentAnalysis pSegmentAnalysis);

private:
    int mId;
    QDate mMeasurementDate;
    BodyCompositionMetrics mComposition;
    BodySegmentAnalysis mSegmentAnalysis;

};

#endif // BODYMEASUREMENTENTRY_H
