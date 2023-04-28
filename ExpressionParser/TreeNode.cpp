//
// Created by Makram.Elghazzaoui on 21/04/2023.
//

#include "TreeNode.h"
#include <list>
#include "ParserToken.h"
#include "utils.h"

#include <iostream>

std::shared_ptr<TreeNode> TreeNode::buildExpressionTree(const std::string &expression) {
    std::vector<ParserToken> tokens;
    ParserToken::getTokens(utils::strTrim(expression), tokens);
    return tokensToTreeNode(tokens);
}

std::shared_ptr<TreeNode> TreeNode::fromOperator(const std::string& symbol) {
    return std::shared_ptr<TreeNode>(new OperatorNode(Operator::getOperator(symbol)));
}

std::shared_ptr<TreeNode> TreeNode::fromNonOperatorToken(const std::string& expression) {
    TreeNode* node = NULL;
    if (!expression.empty()) {
        char c = expression[0];
        if (utils::isNum(c)){
            node = new ConstantNode(expression);
        }
        else if (utils::isAlpha(c)) {
            node = new VariableNode(expression);
        }
    }
    return std::shared_ptr<TreeNode>(node);
}

std::shared_ptr<TreeNode> TreeNode::tokensToTreeNode(const std::vector<ParserToken> &tokens) {
    int minPos = -1;
    unsigned int minPrio;
    // find position of lowest operator priority
    for(auto i=0; i<tokens.size(); ++i) {
        ParserToken token = tokens[i];
        unsigned int prio;
        if (Operator::isOperator(token.getExpression(), prio)) {
            if (minPos == -1 || prio <= minPrio) {
                minPrio = prio;
                minPos = i;
            }
        }
    }

    if (minPos != -1) {
        ParserToken opreratorToken = tokens[minPos];
        std::shared_ptr<TreeNode> node = TreeNode::fromOperator(opreratorToken.getExpression());
        if (node) {
            // left tokens
            std::vector<ParserToken> leftTokens;
            for (auto i = 0; i < minPos; ++i) {
                leftTokens.push_back(tokens[i]);
            }
            // right tokens
            std::vector<ParserToken> rightTokens;
            for (auto i = minPos+1; i < tokens.size(); ++i) {
                rightTokens.push_back(tokens[i]);
            }

            if (!leftTokens.empty()) {
                node->left = tokensToTreeNode(leftTokens);
            }
            if (!rightTokens.empty()) {
                node->right = tokensToTreeNode(rightTokens);
            }
            return node;
        }
    }
    else { // operator is not found: all tokens are: constant, variable or opaque expression
        if (tokens.size() == 1) {
            ParserToken token = tokens[0];
            if (token.isOpaque()) {
                return buildExpressionTree(token.getExpression());
            }
            else {
                return fromNonOperatorToken(token.getExpression());
            }
        }
        else {
            throw std::invalid_argument("Malformed expression: operator is missing.");
        }
    }

    return std::shared_ptr<TreeNode>(NULL);
}
