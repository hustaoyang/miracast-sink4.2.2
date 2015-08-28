
#ifndef TIME_SERIES_H_

#define TIME_SERIES_H_

#include <sys/types.h>

namespace android {

struct TimeSeries {
    TimeSeries();

    void add(double val);

    double mean() const;
    double sdev() const;

private:
    enum {
        kHistorySize = 20
    };
    double mValues[kHistorySize];

    size_t mCount;
    double mSum;
};

}  // namespace android

#endif  // TIME_SERIES_H_

