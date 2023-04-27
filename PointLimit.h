//
// Created by Makram.Elghazzaoui on 18/04/2023.
//

#ifndef TEST_POINTLIMIT_H
#define TEST_POINTLIMIT_H

#include "LimitBase.h"
#include <sstream>

typedef enum {
    LIMIT_LEFT,
    LIMIT_RIGHT,
    LIMIT_DEFAULT
} LimitSide_e;

class PointLimit  : public LimitBase{
private:
    long double x0;
    LimitSide_e side;
protected:
    std::string getTendVers() const {
        std::ostringstream oss;
        oss << x0;
        switch (side) {
            case LIMIT_LEFT:
                oss << '+';
                break;
            case LIMIT_RIGHT:
                oss << '-';
                break;
        }
        return oss.str();
    };
    virtual long double getInitialXValue() const {
        switch (side) {
            case LIMIT_LEFT:
            case LIMIT_DEFAULT:
                return x0 + 1;
            case LIMIT_RIGHT:
                return x0-1;
        }
        return 0;
    };
    virtual long double getStep() const { return 10; };
    virtual void doStep(long double& x) {
        x = x0 + (x-x0)/10;
    };
public:
    PointLimit(FunctionEvaluator& eval, long double x0 = 0, LimitSide_e side = LIMIT_DEFAULT) : LimitBase(eval), x0(x0), side(side) {};
};


#endif //TEST_POINTLIMIT_H
