//
// Created by Makram.Elghazzaoui on 16/04/2023.
//

#ifndef TEST_LIMITBASE_H
#define TEST_LIMITBASE_H

#include "NumberRounder.h"
#include "FunctionEvaluator.h"
#include <iostream>


#define PERIODIC_AT_INFINITY

class LimitBase {
private:
    long double evaluate(long double x);
protected:
    FunctionEvaluator* functionEvaluator;
    unsigned long iter;
    long double limit;
    int limitSign;
    bool isconv;
    long double roundValue(long double x) const;
    virtual std::string getTendVers() const  = 0;
    virtual long double getInitialXValue() const = 0;
    virtual long double getStep() const = 0;;
    virtual void doStep(long double& x) { x += getStep(); };
    int getLimitSign() const { return limitSign; };
public:
    LimitBase(FunctionEvaluator& functionEvaluator) :
            functionEvaluator(&functionEvaluator),
            isconv(false),
            limitSign(0){

    };

    virtual ~LimitBase() {};

    bool isConv() const { return isconv; };
    long double getLimit() const { return limit; };

    virtual void run();
    std::string getConclsion() const;
    void printConclusion(std::ostream& os) const;
    void printConclusion() const { printConclusion(std::cout); };
    NumberRounder round() {
        if (isConv()) {
            NumberRounder nr(getLimit());
            nr.round();
            return nr;
        }
        return NumberRounder(0);
    }
};


#endif //TEST_LIMITBASE_H
