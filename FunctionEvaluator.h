//
// Created by Makram.Elghazzaoui on 16/04/2023.
//

#ifndef TEST_FUNCTIONEVALUATOR_H
#define TEST_FUNCTIONEVALUATOR_H

#include <string>

class FunctionEvaluator {
public:
    virtual long double eval(long double x) const = 0;
    virtual std::string toString() const { return ""; };
};


#endif //TEST_FUNCTIONEVALUATOR_H
