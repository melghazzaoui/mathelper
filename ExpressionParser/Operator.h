//
// Created by Makram.Elghazzaoui on 21/04/2023.
//

#ifndef TEST_OPERATOR_H
#define TEST_OPERATOR_H

#include <string>

#define OPERATOR_PRIO_ADD   1
#define OPERATOR_PRIO_SUB   2
#define OPERATOR_PRIO_DIV   3
#define OPERATOR_PRIO_MUL   4
#define OPERATOR_PRIO_MINUS 5

#include <list>
#include <memory>

class Operator {
private:
    static std::list<std::shared_ptr<Operator>> operatorList;
protected:
    std::string symbol;
public:
    Operator(std::string symbol) : symbol(symbol) {};
    virtual ~Operator() {};
    virtual long double perform(long double left, long double right) const = 0;
    std::string getSymbol() const { return symbol; };
    virtual unsigned int priority() const = 0;
    static bool isOperator(const std::string& expression);
    static std::shared_ptr<Operator> getOperator(const std::string& expression);
    static void initOperatorList();
    static void destroyOperators();
};

class BinaryOperator : public Operator {
public:
    BinaryOperator(std::string symbol) : Operator(symbol) {};
    virtual ~BinaryOperator() {};
};

class OperatorAdd : public BinaryOperator {
public:
    OperatorAdd() : BinaryOperator("+") {};
    virtual ~OperatorAdd() {};
    long double perform(long double left, long double right) const {
        return left + right;
    }
    unsigned int priority() const { return OPERATOR_PRIO_ADD; };
};

class OperatorSub : public BinaryOperator {
public:
    OperatorSub() : BinaryOperator("-") {};
    virtual ~OperatorSub() {};
    long double perform(long double left, long double right) const {
        return left - right;
    }
    unsigned int priority() const { return OPERATOR_PRIO_SUB; };
};

class OperatorMult : public BinaryOperator {
public:
    OperatorMult() : BinaryOperator("*") {};
    virtual ~OperatorMult() {};
    long double perform(long double left, long double right) const {
        return left * right;
    }
    unsigned int priority() const { return OPERATOR_PRIO_MUL; };
};

class OperatorDiv : public BinaryOperator {
public:
    OperatorDiv() : BinaryOperator("/") {};
    virtual ~OperatorDiv() {};
    long double perform(long double left, long double right) const {
        return left / right;
    }
    unsigned int priority() const { return OPERATOR_PRIO_DIV; };
};

class UnaryOperator : public Operator {
public:
    UnaryOperator(std::string symbol) : Operator(symbol) {};
    virtual ~UnaryOperator() {};
};

class OperatorMinus : public UnaryOperator {
public:
    OperatorMinus() : UnaryOperator("-") {};
    virtual ~OperatorMinus() {};
    long double perform(long double left, long double right) const {
        return -right;
    };
    unsigned int priority() const { return OPERATOR_PRIO_MINUS; };
};

#endif //TEST_OPERATOR_H
