#ifndef SEGMENTMETRICS_H
#define SEGMENTMETRICS_H

class SegmentMetrics
{
public:
    SegmentMetrics();
    explicit SegmentMetrics(double pMuscleMassKg,
                            double pFatMassKg,
                            double pFatPercentage,
                            double pLeanMassKg);

    ~SegmentMetrics();

    double getMuscleMassKg() const noexcept;
    void setMuscleMassKg(double pMuscleMassKg) noexcept;

    double getFatMassKg() const noexcept;
    void setFatMassKg(double pFatMassKg) noexcept;

    double getFatPercentage() const noexcept;
    void setFatPercantage(double pFatPercentage) noexcept;

    double pLeanMassKg() const noexcept;
    void setLeanMassKg(double pLeanMassKg) noexcept;

private:
    double mMuscleMassKg;
    double mFatMassKg;
    double mFatPercentage;
    double mLeanMassKg;
};

#endif // SEGMENTMETRICS_H
