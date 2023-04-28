//
// Created by Makram.Elghazzaoui on 27/04/2023.
//

#include "ParserToken.h"
#include "Operator.h"
#include "utils.h"

std::string ParserToken::separators = "+-/*^()[]{}=:,;%!<>@&";

bool ParserToken::isSeparator(char c) {
    return separators.find(c) != separators.npos;
}

size_t getClosingParenthesis(const char* cstr, size_t offset) {
    size_t count = 0;
    size_t len = 0;
    char c;
    while(cstr[offset]) {
        c = cstr[offset++];
        if (c == '(') count++;
        else if (c == ')') count--;

        if(count == 0) {
            return len-1;
        }
        len++;
    }
    return std::string::npos;
}

void ParserToken::getTokens(const std::string &expression, std::vector<ParserToken> &tokens) {
    const char *cstr = expression.c_str();
    std::string exprToken;
    size_t i = 0;
    while (cstr[i]) {
        char c = cstr[i];
        if (isSeparator(c)) {
            exprToken = utils::strTrim(exprToken);
            if (!exprToken.empty()) {
                tokens.push_back(ParserToken(exprToken));
                exprToken.clear();
            }
            if (c != '(') {
                exprToken += c;
                tokens.push_back(ParserToken(exprToken));
                exprToken.clear();
            }
        } else {
            exprToken += c;
        }

        if (c == '(') {
            size_t len = getClosingParenthesis(cstr, i);
            if (len != std::string::npos) {
                exprToken = expression.substr(i+1, len);
                exprToken = utils::strTrim(exprToken);
                if (!exprToken.empty()) {
                    tokens.push_back(ParserToken(exprToken, true));
                    exprToken.clear();
                }
                i++;
                i += len;
                i++;
                continue;
            } else{
                throw std::invalid_argument("Malformed expression.");
            }
        }
        ++i;
    }
    exprToken = utils::strTrim(exprToken);
    if (!exprToken.empty()) {
        tokens.push_back(ParserToken(exprToken));
        exprToken.clear();
    }
}
