//
// Created by Makram.Elghazzaoui on 27/04/2023.
//

#ifndef TEST_PARSERTOKEN_H
#define TEST_PARSERTOKEN_H

#include <string>
#include <vector>
#include <ostream>
#include "utils.h"

class ParserToken {
private:
    bool opaque;
    std::string expression;
    static std::string separators;
    static std::string openingParenthesis;
public:
    ParserToken() : opaque(false) {};
    ParserToken(const std::string& expression) : opaque(false), expression(utils::strTrim(expression)) {};
    ParserToken(const std::string& expression, bool opaque) : opaque(opaque), expression(utils::strTrim(expression)) {};
    std::string getExpression() const { return expression; };
    bool isOpaque() const { return opaque; };
    static bool isSeparator(char c);
    static bool isOpeningParenthesis(char c);
    static void getTokens(const std::string& expression, std::vector<ParserToken>& tokens);
    friend std::ostream& operator<<(std::ostream& os, const ParserToken& token) {
        return os << token.expression;
    }
};

#endif //TEST_PARSERTOKEN_H
