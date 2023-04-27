//
// Created by Makram.Elghazzaoui on 16/04/2023.
//

#include "LimitBase.h"
#include <cmath>
#include <iostream>
#include <sstream>

long double LimitBase::evaluate(long double x) {
    long double fx = functionEvaluator->eval(x);
    if (!(std::isinf(fx) || std::isnan(fx))) {
        limitSign = (fx >= 0) ? 1 : -1;
    }
    return fx;
}

void LimitBase::run() {
#define MAX_ITER 100000000
    iter = 0;
    //std::cout << "Conv loop begin" << std::endl;
    const long double epsilon = 0.0000000001;
    long double diff = -1;
#ifdef PERIODIC_AT_INFINITY
    long double diffSign = -1;
#endif
    long double x = getInitialXValue();
    long double Un = evaluate(x);
    long double Un1;
    do {
        iter++;
        doStep(x);
        Un1 = evaluate(x);
#ifdef PERIODIC_AT_INFINITY
        long double diff0 = diff;
#endif
        diff = std::abs(Un1 - Un);
        Un = Un1;
#ifdef PERIODIC_AT_INFINITY
        if (diff0 != -1) {
            long double diffSign0 = diffSign;
            diffSign = diff - diff0;
            /*if (diffSign > 0) {
                std::cout << "diff sign positive : " << diffSign << "  (" << diffSign0 << ")" << std::endl;
            }*/
        }
#endif
        //std::cout << n << ':' << diff << std::endl;
    } while(
#ifdef PERIODIC_AT_INFINITY
                diffSign <= 0 &&
#endif
                diff > epsilon &&
                !(std::isinf(diff) || std::isnan(diff)) &&
                iter < MAX_ITER
            );
    //std::cout << "Conv loop end" << std::endl;
    isconv =
#ifdef PERIODIC_AT_INFINITY
                (diffSign < 0) &&
#endif
                !(std::isinf(diff) || std::isnan(diff)) &&
                (iter < MAX_ITER);
    if (isconv) {
        limit = Un;
    }
}

long double LimitBase::roundValue(long double x) const {
    long double xint = std::round(x);
    if (std::abs(x-xint) <= ZERO_EPSILON) {
        return xint;
    }
    return x;
}

std::string LimitBase::getConclsion() const {
    std::ostringstream oss;
    printConclusion(oss);
    return oss.str();
}

void LimitBase::printConclusion(std::ostream &os) const {
    os << "lim {x->" << getTendVers() << "} [ " << functionEvaluator->toString() << " ] = ";
    if (isconv) {
        os << roundValue(limit);
    }
    else {
        os << ((getLimitSign()>=0) ? '+' : '-') << "inf";
    }
    os << std::endl;

}