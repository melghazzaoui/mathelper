//
// Created by Makram.Elghazzaoui on 21/04/2023.
//

#include "TreeNode.h"
#include <list>
#include "ParserToken.h"


#include <iostream>

std::shared_ptr<TreeNode> TreeNode::buildExpressionTree(const std::string &expression) {
    std::vector<ParserToken> tokens;
    ParserToken::getTokens(expression, tokens);

    for(auto i=0; i<tokens.size(); ++i) {
        std::cout << tokens[i] << std::endl;

    }
}