#include "segmentmetrics.h"

SegmentMetrics::SegmentMetrics()
    : mMuscleMassKg(0.0)
    , mFatMassKg(0.0)
    , mFatPercentage(0.0)
    , mLeanMassKg(0.0)
{

}

SegmentMetrics::SegmentMetrics(double pMuscleMassKg, double pFatMassKg, double pFatPercentage, double pLeanMassKg)
    : mMuscleMassKg(pMuscleMassKg)
    , mFatMassKg(pFatMassKg)
    , mFatPercentage(pFatPercentage)
    , mLeanMassKg(pLeanMassKg)
{

}

SegmentMetrics::~SegmentMetrics() = default;

double SegmentMetrics::getMuscleMassKg() const noexcept
{
    return mMuscleMassKg;
}

void SegmentMetrics::setMuscleMassKg(double pMuscleMassKg) noexcept
{
    mMuscleMassKg = pMuscleMassKg;
}

double SegmentMetrics::getFatMassKg() const noexcept
{
    return mFatMassKg;
}

void SegmentMetrics::setFatMassKg(double pFatMassKg) noexcept
{
    mFatMassKg = pFatMassKg;
}

double SegmentMetrics::getFatPercentage() const noexcept
{
    return mFatPercentage;
}

void SegmentMetrics::setFatPercantage(double pFatPercentage) noexcept
{
    mFatPercentage = pFatPercentage;
}

double SegmentMetrics::getLeanMassKg() const noexcept
{
    return mLeanMassKg;
}

void SegmentMetrics::setLeanMassKg(double pLeanMassKg) noexcept
{
    mLeanMassKg = pLeanMassKg;
}
