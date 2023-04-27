//
// Created by Makram.Elghazzaoui on 21/04/2023.
//

#include "TreeNode.h"
#include <list>

bool TreeNode::isAlpha(char c) {
    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') || (c == '_');
}

bool TreeNode::isNum(char c) {
    return ('0' <= c && c <= '9') || (c == '.');
}

bool TreeNode::isAlphaNum(char c) {
    return isAlpha(c) || isNum(c);
}

TreeNode* TreeNode::createNodeFromAlphanum(const std::string &alphanum) {
    if (alphanum.empty()) {
        return NULL;
    }
    char c = alphanum[0];
    if (isAlpha(c)) {
        if (Operator::isOperator(alphanum)) {
            return new OperatorNode(Operator::getOperator(alphanum));
        }
        else {
            return new VariableNode(alphanum);
        }
    }
    else if (isNum(c)) {
        return new ConstantNode(alphanum);
    }
    return NULL;
}

std::shared_ptr<TreeNode> TreeNode::createTreeFromChildren(const std::list<std::shared_ptr<TreeNode>>& children) {
    auto itMinPrio = children.begin();
    int minprio = -1;
    for(auto it = children.begin(); it != children.end(); ++it) {
        TreeNode*  node = it->get();
        OperatorNode* oprNode = dynamic_cast<OperatorNode*>(node);
        if (oprNode != NULL && !oprNode->built()) {
            if (minprio == -1 || oprNode->priority() <= minprio) {
                minprio = oprNode->priority();
                itMinPrio = it;
            }
        }
    }

    if (itMinPrio != children.end() && *itMinPrio) {
        // left
        std::list<std::shared_ptr<TreeNode>> leftChildren;
        for (auto it = children.begin(); it != itMinPrio; ++it) {
            leftChildren.push_back(*it);
        }
        if (!leftChildren.empty()) {
            (*itMinPrio)->left = createTreeFromChildren(leftChildren);
        }

        // right
        std::list<std::shared_ptr<TreeNode>> rightChildren;
        auto itRight = itMinPrio;
        itRight++;
        for (auto it = itRight; it != children.end(); ++it) {
            rightChildren.push_back(*it);
        }
        if (!rightChildren.empty()) {
            (*itMinPrio)->right = createTreeFromChildren(rightChildren);
        }
        return *itMinPrio;
    }



    return std::shared_ptr<TreeNode>(NULL);

}

std::shared_ptr<TreeNode> handleNestedExpression(const std::string& expression) {
    std::shared_ptr<TreeNode> nestedNode = TreeNode::buildExpressionTree(expression);
    return nestedNode;
}

std::shared_ptr<TreeNode> TreeNode::buildExpressionTree(const std::string &expression) {
    unsigned int parenthesis = 0;
    std::string nestedExpression;
    std::list<std::shared_ptr<TreeNode>> children;
    std::string alphaNumToken;
    std::string specialCharToken;

    for(char c : expression) {
        if (c == '(') {
            if (!specialCharToken.empty()) {
                if (Operator::isOperator(specialCharToken)) {
                    children.push_back(
                            makeSharedTreeNode(new OperatorNode(Operator::getOperator(specialCharToken))));
                }
                specialCharToken.clear();
            }
            parenthesis++;
            if (parenthesis == 1) {
                continue;
            }
        } else if (c == ')') {
            parenthesis--;
            if (!specialCharToken.empty()) {
                specialCharToken.clear();
                throw std::invalid_argument("Malformed expression.");
            }
        }
        // handle nested expression
        if (parenthesis > 0) {
            nestedExpression += c;
        }
        else if (!nestedExpression.empty()) {
            if (parenthesis == 0) {
                std::shared_ptr<TreeNode> nestedNode = handleNestedExpression(nestedExpression);
                children.push_back(nestedNode);
                nestedExpression.clear();
            }
            else {
                throw std::invalid_argument("Extra parenthesis found.");
            }
        }
        else {

            if (isAlphaNum(c)) {
                alphaNumToken += c;
                if (!specialCharToken.empty()) {
                    if (Operator::isOperator(specialCharToken)) {
                        children.push_back(
                                makeSharedTreeNode(new OperatorNode(Operator::getOperator(specialCharToken))));
                    }
                    specialCharToken.clear();
                }
            } else {
                if (!alphaNumToken.empty()) {
                    TreeNode *node = createNodeFromAlphanum(alphaNumToken);
                    if (node != NULL) {
                        children.push_back(makeSharedTreeNode(node));
                    }
                    alphaNumToken.clear();
                }
                if (c != '(' && c != ')') {
                    specialCharToken += c;
                }
            }
        }
    }

    if (!alphaNumToken.empty()) {
        TreeNode* node = createNodeFromAlphanum(alphaNumToken);
        if (node != NULL) {
            children.push_back(makeSharedTreeNode(node));
        }
        alphaNumToken.clear();
    }
    if (!specialCharToken.empty()) {
        throw std::invalid_argument("Malformed expression.");
    }

    return createTreeFromChildren(children);
}