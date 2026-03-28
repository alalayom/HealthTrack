#include "bodymeasuremententry.h"

BodyMeasurementEntry::BodyMeasurementEntry()
    : mId(-1)
    , mMeasurementDate(QDate::currentDate())
{

}

BodyMeasurementEntry::BodyMeasurementEntry(int pId, QDate pMeasurementDate, BodyCompositionMetrics pComposition, BodySegmentAnalysis pSegmentAnalysis)
    : mId(pId)
    , mMeasurementDate(std::move(pMeasurementDate))
    , mComposition(std::move(pComposition))
    , mSegmentAnalysis(std::move(pSegmentAnalysis))
{

}

BodyMeasurementEntry::~BodyMeasurementEntry() = default;

int BodyMeasurementEntry::getId() const noexcept
{
    return mId;
}

void BodyMeasurementEntry::setId(int pId) noexcept
{
    mId = pId;
}

const QDate &BodyMeasurementEntry::getMeasurementDate() const noexcept
{
    return mMeasurementDate;
}

void BodyMeasurementEntry::setMeasurementDate(QDate pMeasurementDate)
{
    mMeasurementDate = std::move(pMeasurementDate);
}

const BodyCompositionMetrics &BodyMeasurementEntry::getComposition() const noexcept
{
    return mComposition;
}

void BodyMeasurementEntry::setComposition(BodyCompositionMetrics pComposition)
{
    mComposition = std::move(pComposition);
}

const BodySegmentAnalysis &BodyMeasurementEntry::getSegmentAnalysis() const noexcept
{
    return mSegmentAnalysis;
}

void BodyMeasurementEntry::setSegmentAnalysis(BodySegmentAnalysis pSegmentAnalysis)
{
    mSegmentAnalysis = std::move(pSegmentAnalysis);
}
