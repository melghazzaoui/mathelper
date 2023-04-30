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


#include "TreeNode.h"
#include "utils.h"
#include <assert.h>

#define COUT std::cout
#define CRLF std::endl

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



void test1() {
    COUT << "Running test " << __FUNCTION__ << CRLF;
    auto node = TreeNode::buildExpressionTree("1+2");
    auto res = node->eval(0);
    assert(res == 3);
}

void test2() {
    COUT << "Running test " << __FUNCTION__ << CRLF;
    auto node = TreeNode::buildExpressionTree("1-(2+3.5)");
    auto res = node->eval(0);
    assert(res == -4.5);
}

void test3() {
    COUT << "Running test " << __FUNCTION__ << CRLF;
    auto node = TreeNode::buildExpressionTree("(5+1-2-5)");
    auto res = node->eval(0);
    assert(res == -1);
}

void test4() {
    COUT << "Running test " << __FUNCTION__ << CRLF;
    auto node = TreeNode::buildExpressionTree("1+2/3*3");
    auto res = node->eval(0);
    assert(res == 3);
}

void test5() {
    COUT << "Running test " << __FUNCTION__ << CRLF;
    auto node = TreeNode::buildExpressionTree("1+2/3*log(exp(3))");
    auto res = node->eval(0);
    assert(res == 3);
}

void test6() {
    COUT << "Running test " << __FUNCTION__ << CRLF;
    auto node = TreeNode::buildExpressionTree("6^3/6^2");
    auto res = node->eval(0);
    assert(res == 6);
}

void test7() {
    COUT << "Running test " << __FUNCTION__ << CRLF;
    auto node = TreeNode::buildExpressionTree("-5");
    auto res = node->eval(0);
    assert(res == -5);
}

void testLog() {
    COUT << "Running test " << __FUNCTION__ << CRLF;
    auto node = TreeNode::buildExpressionTree("log(x)");
    assert(node->eval(1) == 0);
    assert(node->eval(2) == std::log((long double)2));
}

void testExp() {
    COUT << "Running test " << __FUNCTION__ << CRLF;
    auto node = TreeNode::buildExpressionTree("exp(x)");
    assert(node->eval(0) == 1.0L);
    assert(node->eval(2) == std::exp((long double)2));
}

void testNestedFunctions() {
    COUT << "Running test " << __FUNCTION__ << CRLF;
    auto node = TreeNode::buildExpressionTree("exp(log(x))");
    assert(node->eval(0) == 0.0L);
    assert(node->eval(2) == 2.0L);
}

void testNestedFunctions1() {
    COUT << "Running test " << __FUNCTION__ << CRLF;
    auto node = TreeNode::buildExpressionTree("log(exp(x))");
    assert(node->eval(0) == 0.0L);
    assert(node->eval(2) == 2.0L);
}

void testCos() {
    COUT << "Running test " << __FUNCTION__ << CRLF;
    auto node = TreeNode::buildExpressionTree("cos(n*3.14159265358979323846264338327950288419716939937510)");
    assert(node->eval(0) == 1.0L);
    assert(node->eval(1) == -1.0L);
}

void testSin() {
    COUT << "Running test " << __FUNCTION__ << CRLF;
    auto node = TreeNode::buildExpressionTree("sin(n*3.14159265358979323846264338327950288419716939937510)");
    assert(node->eval(0) == 0.0L);
    assert(node->eval(0.5) == 1.0L);
}

void testComplexExpression() {
    COUT << "Running test " << __FUNCTION__ << CRLF;
    auto node = TreeNode::buildExpressionTree("1.5 + 3/2 + (13 - 2 - 3 + 1 + 5/5 )");
    assert(node->eval() == 13.0L);
}

void run_TNR() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    testLog();
    testExp();
    testNestedFunctions();
    testNestedFunctions1();
    testCos();
    testSin();
    testComplexExpression();
    COUT << CRLF << "------ NON-REG TESTS ARE OK ------" << CRLF;
}

int main() {
    Operator::initOperatorList();
    run_TNR();
}
