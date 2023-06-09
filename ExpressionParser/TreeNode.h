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
#include "Operator.h"

typedef std::map<std::string, long double> variableMap_t;

class TreeNode {
private:
    static bool isAlpha(char c);
    static bool isNum(char c);
    static bool isAlphaNum(char c);
    static std::shared_ptr<TreeNode> makeSharedTreeNode(TreeNode* node) {
        return std::shared_ptr<TreeNode>(node);
    }
protected:
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;
    static TreeNode* createNodeFromAlphanum(const std::string& alphanum);
    static std::shared_ptr<TreeNode> createTreeFromChildren(const std::list<std::shared_ptr<TreeNode>>& children);
public:
    TreeNode() : left(std::shared_ptr<TreeNode>(NULL)), right(std::shared_ptr<TreeNode>(NULL)) {};
    TreeNode(std::shared_ptr<TreeNode> left, std::shared_ptr<TreeNode> right) : left(left), right(right) {};
    virtual long double eval(const variableMap_t& varmap) const = 0;
    static std::shared_ptr<TreeNode> buildExpressionTree(const std::string& expression);
};

class ConstantNode : public TreeNode {
protected:
    long double value;
public:
    ConstantNode(const std::string& expression) : TreeNode() {
        std::istringstream iss(expression);
        iss >> value;
    };

    long double eval(const variableMap_t& varmap) const {
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

    bool built() const {
        return left || right;
    }
};


#endif //TEST_TREENODE_H
