//
// Created by Makram.Elghazzaoui on 20/04/2023.
//

#include "NumberRounder.h"
#include <cmath>

bool NumberRounder::round(long double x, long double& xint) const {
    xint = std::round(x);
    return std::abs(x-xint) <= ZERO_EPSILON;
}

void NumberRounder::round() {
    long double xint;
    if (round(x, xint)) {
        result = std::shared_ptr<MathNumber>(new BasicNumber(xint));
    }
    int n = 6;
    for(auto i=1; i<=n && !result; ++i) {
        long double q = i*x/M_PI;
        long double qint;
        if (round(q, qint)) {
            result = std::shared_ptr<MathNumber>(new TrigoNumber(x, qint, i));
        }
    }
}