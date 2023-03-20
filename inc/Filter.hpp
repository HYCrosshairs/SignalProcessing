#pragma once

namespace signal::filter
{
enum class FilterType
{
    LOWPASS,
    HIGHPASS,
    BANDPASS,
    ALLPASS,
    PEAK,
    KALMAN,
    NEWFILTER
};

class Filter
{
private:
    /* data */
public:
    Filter(/* args */);
    ~Filter();
};
} // namespace signal::filter