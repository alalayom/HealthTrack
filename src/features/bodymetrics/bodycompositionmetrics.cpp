#include "bodycompositionmetrics.h"



BodyCompositionMetrics::BodyCompositionMetrics()
    : mWeightKg(0.0)
    , mMuscleMassKg(0.0)
    , mMusclePercentage(0.0)
    , mFatMassKg(0.0)
    , mFatPercentage(0.0)
    , mLeanMassKg(0.0)
    , mBodyWaterMassKg(0.0)
    , mBodyWaterPercentage(0.0)
    , mBmi(0.0)
    , mBmr(0.0)
{

}

BodyCompositionMetrics::BodyCompositionMetrics(double pWeightKg, double pMuscleMassKg,
                                               double pMusclePercentage, double pFatMassKg,
                                               double pFatPercentage, double pLeanMassKg,
                                               double pBodyWaterMassKg, double pBodyWaterPercentage,
                                               double pBmi, double pBmr)
    : mWeightKg(pWeightKg)
    , mMuscleMassKg(pMuscleMassKg)
    , mMusclePercentage(pMusclePercentage)
    , mFatMassKg(pFatMassKg)
    , mFatPercentage(pFatPercentage)
    , mLeanMassKg(pLeanMassKg)
    , mBodyWaterMassKg(pBodyWaterMassKg)
    , mBodyWaterPercentage(pBodyWaterPercentage)
    , mBmi(pBmi)
    , mBmr(pBmr)
{

}

BodyCompositionMetrics::~BodyCompositionMetrics() = default;

double BodyCompositionMetrics::getWeightKg() const noexcept
{
    return mWeightKg;
}

void BodyCompositionMetrics::setWeightKg(double pWeightKg) noexcept
{
    mWeightKg = pWeightKg;
}

double BodyCompositionMetrics::getMuscleMassKg() const noexcept
{
    return mMuscleMassKg;
}

void BodyCompositionMetrics::setMuscleMassKg(double pMuscleMassKg) noexcept
{
    mMuscleMassKg = pMuscleMassKg;
}

double BodyCompositionMetrics::getMusclePercentage() const noexcept
{
    return mMusclePercentage;
}

void BodyCompositionMetrics::setMusclePercentage(double pMusclePercentage) noexcept
{
    mMusclePercentage = pMusclePercentage;
}

double BodyCompositionMetrics::getFatMassKg() const noexcept
{
    return mFatMassKg;
}

void BodyCompositionMetrics::setFatMassKg(double pFatMassKg) noexcept
{
    mFatMassKg = pFatMassKg;
}

double BodyCompositionMetrics::getFatPercentage() const noexcept
{
    return mFatPercentage;
}

void BodyCompositionMetrics::setFatPercentage(double pFatPercentage) noexcept
{
    mFatPercentage = pFatPercentage;
}

double BodyCompositionMetrics::getLeanMassKg() const noexcept
{
    return mLeanMassKg;
}

void BodyCompositionMetrics::setLeanMassKg(double pLeanMassKg) noexcept
{
    mLeanMassKg = pLeanMassKg;
}

double BodyCompositionMetrics::getBodyWaterMassKg() const noexcept
{
    return mBodyWaterMassKg;
}

void BodyCompositionMetrics::setBodyWaterMassKg(double pBodyWaterMassKg) noexcept
{
    mBodyWaterMassKg = pBodyWaterMassKg;
}

double BodyCompositionMetrics::getBodyWaterPercentage() const noexcept
{
    return mBodyWaterPercentage;
}

void BodyCompositionMetrics::setBodyWaterPercentage(double pBodyWaterPercentage) noexcept
{
    mBodyWaterPercentage = pBodyWaterPercentage;
}

double BodyCompositionMetrics::getBmi() const noexcept
{
    return mBmi;
}

void BodyCompositionMetrics::setBmi(double pBmi) noexcept
{
    mBmi = pBmi;
}

double BodyCompositionMetrics::getBmr() const noexcept
{
    return mBmr;
}

void BodyCompositionMetrics::setBmr(double pBmr) noexcept
{
    mBmr = pBmr;
}
