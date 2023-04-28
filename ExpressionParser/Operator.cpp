//
// Created by Makram.Elghazzaoui on 21/04/2023.
//

#include "Operator.h"

std::list<std::shared_ptr<Operator>> Operator::operatorList;

void Operator::initOperatorList() {
    operatorList.push_back(std::shared_ptr<Operator>(new OperatorAdd())); // +
    operatorList.push_back(std::shared_ptr<Operator>(new OperatorSub())); // -
    operatorList.push_back(std::shared_ptr<Operator>(new OperatorMult())); // *
    operatorList.push_back(std::shared_ptr<Operator>(new OperatorDiv())); // /
    operatorList.push_back(std::shared_ptr<Operator>(new OperatorMinus())); // - (unary)
    operatorList.push_back(std::shared_ptr<Operator>(new OperatorPow())); // ^
    operatorList.push_back(std::shared_ptr<Operator>(new MathLogOperator())); // log
    operatorList.push_back(std::shared_ptr<Operator>(new MathExpOperator())); // exp
    operatorList.push_back(std::shared_ptr<Operator>(new MathCosOperator())); // cos
    operatorList.push_back(std::shared_ptr<Operator>(new MathSinOperator())); // sin
}

bool Operator::isOperator(const std::string &expression) {
    for(auto opr : operatorList) {
        if (opr->getSymbol() == expression) {
            return true;
        }
    }
    return false;
}

bool Operator::isOperator(const std::string &expression, unsigned int& priority) {
    for(auto opr : operatorList) {
        if (opr->getSymbol() == expression) {
            priority = opr->priority();
            return true;
        }
    }
    return false;
}

std::shared_ptr<Operator> Operator::getOperator(const std::string &expression) {
    for(auto opr : operatorList) {
        if (opr->getSymbol() == expression) {
            return opr;
        }
    }
    return std::shared_ptr<Operator>(NULL);
}