//
// Created by Makram.Elghazzaoui on 21/04/2023.
//

#ifndef TEST_TREENODE_H
#define TEST_TREENODE_H

#include <memory>
#include <string>
#include <map>
#include <sstream>
#include <list>
#include <vector>
#include "Operator.h"
#include "ParserToken.h"
#include "utils.h"
#include <iostream>

typedef std::map<std::string, long double> variableMap_t;

class TreeNode {
private:
    static std::shared_ptr<TreeNode> makeSharedTreeNode(TreeNode* node) {
        return std::shared_ptr<TreeNode>(node);
    }
protected:
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;
public:
    TreeNode() : left(std::shared_ptr<TreeNode>(NULL)), right(std::shared_ptr<TreeNode>(NULL)) {};
    TreeNode(std::shared_ptr<TreeNode> left, std::shared_ptr<TreeNode> right) : left(left), right(right) {};
    virtual ~TreeNode() { std::cout << "destroy" << std::endl; }
    virtual long double eval(const variableMap_t& varmap) const = 0;
    virtual long double eval(long double x) const  = 0;
    static std::shared_ptr<TreeNode> buildExpressionTree(const std::string& expression);

    static std::shared_ptr<TreeNode> tokensToTreeNode(const std::vector<ParserToken> &tokens);
    static std::shared_ptr<TreeNode> fromOperator(const std::string& symbol);
    static std::shared_ptr<TreeNode> fromNonOperatorToken(const std::string& expression);
};

class ConstantNode : public TreeNode {
protected:
    long double value;
public:
    ConstantNode(const std::string& expression) : TreeNode() {
        value = utils::strToLongDoule(expression);
    };

    long double eval(const variableMap_t& varmap) const {
        return value;
    }

    long double eval(long double x) const {
        return value;
    }
};

class VariableNode : public TreeNode {
protected:
    std::string id;
public:
    VariableNode(const std::string& id) : TreeNode(), id(id) {};

    long double eval(const variableMap_t& varmap) const {
        auto it = varmap.find(id);
        if (it != varmap.end()) {
            return it->second;
        }
        return 0;
    }

    long double eval(long double x) const {
        return x;
    }
};

class OperatorNode : public TreeNode {
protected:
    std::shared_ptr<Operator> opr;
public:
    OperatorNode(const std::shared_ptr<Operator>& opr): TreeNode(), opr(opr) {};
    unsigned int priority() const {
        return opr->priority();
    };

    long double eval(const variableMap_t& varmap) const {
        long double leftValue, rightValue;
        if (left) {
            leftValue = left->eval(varmap);
        }
        if (right) {
            rightValue = right->eval(varmap);
        }
        return opr->perform(leftValue, rightValue);
    };

    long double eval(long double x) const {
        long double leftValue, rightValue;
        if (left) {
            leftValue = left->eval(x);
        }
        if (right) {
            rightValue = right->eval(x);
        }
        return opr->perform(leftValue, rightValue);
    }

    bool built() const {
        return left || right;
    }
};


#endif //TEST_TREENODE_H
