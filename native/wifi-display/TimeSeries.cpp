
#include "TimeSeries.h"

#include <math.h>
#include <string.h>

namespace android {

TimeSeries::TimeSeries()
    : mCount(0),
      mSum(0.0) {
}

void TimeSeries::add(double val) {
    if (mCount < kHistorySize) {
        mValues[mCount++] = val;
        mSum += val;
    } else {
        mSum -= mValues[0];
        memmove(&mValues[0], &mValues[1], (kHistorySize - 1) * sizeof(double));
        mValues[kHistorySize - 1] = val;
        mSum += val;
    }
}

double TimeSeries::mean() const {
    if (mCount < 1) {
        return 0.0;
    }

    return mSum / mCount;
}

double TimeSeries::sdev() const {
    if (mCount < 1) {
        return 0.0;
    }

    double m = mean();

    double sum = 0.0;
    for (size_t i = 0; i < mCount; ++i) {
        double tmp = mValues[i] - m;
        tmp *= tmp;

        sum += tmp;
    }

    return sqrt(sum / mCount);
}

}  // namespace android
