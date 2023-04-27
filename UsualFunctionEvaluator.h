//
// Created by Makram.Elghazzaoui on 16/04/2023.
//

#ifndef TEST_USUALFUNCTIONEVALUATOR_H
#define TEST_USUALFUNCTIONEVALUATOR_H
#include <cmath>
#include "FunctionEvaluator.h"

class LogEvaluator : public FunctionEvaluator {
public:
    LogEvaluator(const LogEvaluator& le) : FunctionEvaluator(le) {

    }

    LogEvaluator(LogEvaluator* le) : FunctionEvaluator(*le) {};

    LogEvaluator() : FunctionEvaluator() {};
    long double eval(long double x) const {
        return log(x);
    };

    std::string toString() const {
        return "log(x)";
    };
};

class ExpEvaluator : public FunctionEvaluator {
public:
    long double eval(long double x) const {
        return exp(x);
    };

    std::string toString() const {
        return "exp(x)";
    };
};

class SqrtEvaluator : public FunctionEvaluator {
public:
    long double eval(long double x) const {
        return sqrt(x);
    };

    std::string toString() const {
        return "sqrt(x)";
    };
};

class CosEvaluator : public FunctionEvaluator {
public:
    long double eval(long double x) const {
        return cos(x);
    };

    std::string toString() const {
        return "cos(x)";
    };
};

class SinEvaluator : public FunctionEvaluator {
public:
    long double eval(long double x) const {
        return sin(x);
    };

    std::string toString() const {
        return "sin(x)";
    };
};

#endif //TEST_USUALFUNCTIONEVALUATOR_H
