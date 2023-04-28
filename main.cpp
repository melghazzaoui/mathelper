#include <iostream>

#include "SvModuleGenerator.h"
#include <fstream>
#include <cmath>
#include "UsualFunctionEvaluator.h"
#include "LimitBase.h"
#include <list>
#include <memory>

#include "PointLimit.h"
#include "InfinityLimit.h"

const long double PI = 3.14159265358979323846264338327950288419716939937510;

using namespace std;


long double U(long double x) {
    long double _1 = 1;
    return _1/log(x);
}




class Eval1 : public FunctionEvaluator {
public:
    Eval1() : FunctionEvaluator() {};
    Eval1(Eval1* e) : FunctionEvaluator(*e) {};
    long double eval(long double x) const {
        long double _1 = 1;
        return std::log(exp(35*M_PI/40) + _1/x);
    };
    std::string toString() const {
        return "log(exp(5/7 Pi)+1/x)";
    };
};

class InfinityBothLimit {
private:
    InfinityLimit* positive;
    InfinityLimit* negative;
public:
    InfinityBothLimit(FunctionEvaluator& functionEvaluator) {
        positive = new InfinityLimit(functionEvaluator);
        negative = new InfinityLimit(functionEvaluator, LimitInfinitySide_e::LIMIT_INFINITY_NEGATIVE);
    }

    virtual ~InfinityBothLimit() {
        delete positive;
        delete negative;
    }

    void run();
    void printConclusion(std::ostream& os) const {
        positive->printConclusion(os);
        negative->printConclusion(os);
    }

    void printConclusion() const {
        printConclusion(std::cout);
    }

    InfinityLimit* getPositiveLimit() const { return positive; };
    InfinityLimit* getNegativeLimit() const { return negative; };
};

void InfinityBothLimit::run() {
    positive->run();
    negative->run();
}

std::list<std::shared_ptr<FunctionEvaluator>> evaluators;

void initEvaluators() {
    evaluators.push_back(std::make_shared<Eval1>(new Eval1()));
    /*evaluators.push_back(ExpEvaluator());
    evaluators.push_back(SqrtEvaluator());
    evaluators.push_back(Eval1());*/
}

void deleteEvaluators() {
    /*for(FunctionEvaluator* eval : evaluators) {
        delete eval;
    }*/
}

#include "NumberRounder.h"

void findLimit(FunctionEvaluator& functionEvaluator, long double x0, LimitSide_e side = LimitSide_e::LIMIT_DEFAULT) {
    PointLimit ptLimit(functionEvaluator, x0, side);
    ptLimit.run();
    ptLimit.printConclusion();
    std::cout << "Round limit : " << ptLimit.round() << std::endl;
}

void findLimit(FunctionEvaluator& functionEvaluator, LimitInfinitySide_e side = LimitInfinitySide_e::LIMIT_INFINITY_POSITIVE) {
    InfinityLimit ptLimit(functionEvaluator, side);
    ptLimit.run();
    ptLimit.printConclusion();
    NumberRounder nr = ptLimit.round();
    std::cout << "Round limit : " << nr << std::endl;
}


#include "TreeNode.h"
#include "utils.h"

#define COUT std::cout
#define CRLF std::endl

int main() {
    variableMap_t varmap;
    varmap.insert(make_pair("x",34.6));
    Operator::initOperatorList();
    auto node = TreeNode::buildExpressionTree(".1 + log(exp(x))");
    auto res = node->eval(varmap);
    std::cout << "RES = " << res << std::endl;

}
