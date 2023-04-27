//
// Created by Makram.Elghazzaoui on 19/04/2023.
//

#ifndef TEST_INFINITYLIMIT_H
#define TEST_INFINITYLIMIT_H

#include "LimitBase.h"

typedef enum {
    LIMIT_INFINITY_POSITIVE,
    LIMIT_INFINITY_NEGATIVE
} LimitInfinitySide_e;

class InfinityLimit : public LimitBase {
private:
    LimitInfinitySide_e side;

protected:
    virtual std::string getTendVers() const {
        switch (side) {
            case LIMIT_INFINITY_POSITIVE:
                return "+inf";
            case LIMIT_INFINITY_NEGATIVE:
                return "-inf";
        }
        return "?";
    };

    virtual long double getInitialXValue() const {
        switch (side) {
            case LIMIT_INFINITY_POSITIVE:
                return 10000;
            case LIMIT_INFINITY_NEGATIVE:
                return -10000;
        }
        return 0;
    };

    virtual long double getStep() const {
        switch (side) {
            case LIMIT_INFINITY_POSITIVE:
                return 500;
            case LIMIT_INFINITY_NEGATIVE:
                return -500;
        }
        return 0;
    };

public:
    InfinityLimit(FunctionEvaluator& functionEvaluator, LimitInfinitySide_e side = LIMIT_INFINITY_POSITIVE) :
        LimitBase(functionEvaluator),
        side(side) {

    };
    virtual ~InfinityLimit() {};
};


#endif //TEST_INFINITYLIMIT_H
