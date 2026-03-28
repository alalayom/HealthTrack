#ifndef BODYSEGMENTANALYSIS_H
#define BODYSEGMENTANALYSIS_H

#include <utility>

#include "segmentmetrics.h"

class BodySegmentAnalysis
{
public:
    BodySegmentAnalysis();
    explicit BodySegmentAnalysis(SegmentMetrics pTrunk,
                                 SegmentMetrics pRightArm,
                                 SegmentMetrics pLeftArm,
                                 SegmentMetrics pRightLeg,
                                 SegmentMetrics pLeftLeg);

    ~BodySegmentAnalysis();

    const SegmentMetrics& getTrunk() const noexcept;
    void setTrunk(SegmentMetrics pTrunk);

    const SegmentMetrics& getRightArm() const noexcept;
    void setRightArm(SegmentMetrics pRightArm);

    const SegmentMetrics& getLeftArm() const noexcept;
    void setLeftArm(SegmentMetrics pLeftArm);

    const SegmentMetrics& getRightLeg() const noexcept;
    void setRightLeg(SegmentMetrics pRightLeg);

    const SegmentMetrics& getLeftLeg() const noexcept;
    void setLeftLeg(SegmentMetrics pLeftLeg);

private:
    SegmentMetrics mTrunk;
    SegmentMetrics mRightArm;
    SegmentMetrics mLeftArm;
    SegmentMetrics mRightLeg;
    SegmentMetrics mLeftLeg;
};

#endif // BODYSEGMENTANALYSIS_H
