#include "bodysegmentanalysis.h"
#include <utility>

BodySegmentAnalysis::BodySegmentAnalysis()
    : mTrunk()
    , mRightArm()
    , mLeftArm()
    , mRightLeg()
    , mLeftLeg()
{

}

BodySegmentAnalysis::BodySegmentAnalysis(SegmentMetrics pTrunk,
                                         SegmentMetrics pRightArm,
                                         SegmentMetrics pLeftArm,
                                         SegmentMetrics pRightLeg,
                                         SegmentMetrics pLeftLeg)
    : mTrunk(std::move(pTrunk))
    , mRightArm(std::move(pRightArm))
    , mLeftArm(std::move(pLeftArm))
    , mRightLeg(std::move(pRightLeg))
    , mLeftLeg(std::move(pLeftLeg))
{

}

BodySegmentAnalysis::~BodySegmentAnalysis() = default;

const SegmentMetrics &BodySegmentAnalysis::getTrunk() const noexcept
{
    return mTrunk;
}

void BodySegmentAnalysis::setTrunk(SegmentMetrics pTrunk)
{
    mTrunk = std::move(pTrunk);
}

const SegmentMetrics &BodySegmentAnalysis::getRightArm() const noexcept
{
    return mRightArm;
}

void BodySegmentAnalysis::setRightArm(SegmentMetrics pRightArm)
{
    mRightArm = std::move(pRightArm);
}

const SegmentMetrics &BodySegmentAnalysis::getLeftArm() const noexcept
{
    return mLeftArm;
}

void BodySegmentAnalysis::setLeftArm(SegmentMetrics pLeftArm)
{
    mLeftArm = std::move(pLeftArm);
}

const SegmentMetrics &BodySegmentAnalysis::getRightLeg() const noexcept
{
    return mRightLeg;
}

void BodySegmentAnalysis::setRightLeg(SegmentMetrics pRightLeg)
{
    mRightLeg = std::move(pRightLeg);
}

const SegmentMetrics &BodySegmentAnalysis::getLeftLeg() const noexcept
{
    return mLeftLeg;
}

void BodySegmentAnalysis::setLeftLeg(SegmentMetrics pLeftLeg)
{
    mLeftLeg = std::move(pLeftLeg);
}
