//
// Created by Makram.Elghazzaoui on 27/04/2023.
//

#include "ParserToken.h"
#include "Operator.h"
#include "utils.h"

std::string ParserToken::separators = "+-/*^()[]{}=:,;%!<>@&";
std::string ParserToken::openingParenthesis = "([{";

bool ParserToken::isSeparator(char c) {
    return separators.find(c) != separators.npos;
}

bool ParserToken::isOpeningParenthesis(char c) {
    return openingParenthesis.find(c) != openingParenthesis.npos;
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

typedef enum {
    PARSING_STATE_NOTHING,
    PARSING_STATE_OPERATOR,
    PARSING_STATE_EXPRESSION,
    PARSING_STATE_OPAQUE
} ParsingState_e;

std::string stateToString(ParsingState_e state) {
    switch (state) {
        case PARSING_STATE_EXPRESSION:
            return "PARSING_STATE_EXPRESSION";
        case PARSING_STATE_OPERATOR:
            return "PARSING_STATE_OPERATOR";
        case PARSING_STATE_NOTHING:
            return "PARSING_STATE_NOTHING";
        case PARSING_STATE_OPAQUE:
            return "PARSING_STATE_OPAQUE";
    }
    return "UNKNOWN STATE";
}

void setParsingState(ParsingState_e& oldState, ParsingState_e newState, const std::string& token) {
    //std::cout << "TRANSITION: " << stateToString(oldState) << " -> " << stateToString(newState) << " " << token << std::endl;
    oldState = newState;
}

#define PUSH_TOKEN(token) tokens.push_back(ParserToken(token))
#define PUSH_TOKEN_OPAQUE(token) tokens.push_back(ParserToken(token,true))

void ParserToken::getTokens(const std::string &expression, std::vector<ParserToken> &tokens) {
    ParsingState_e state = PARSING_STATE_NOTHING;
    setParsingState(state, PARSING_STATE_EXPRESSION, "");
    const char *cstr = expression.c_str();
    std::string exprToken;
    size_t i = 0;
    while (cstr[i]) {
        char c = cstr[i];
        if (isSeparator(c)) {
            switch (state) {
                case PARSING_STATE_EXPRESSION:
                    exprToken = utils::strTrim(exprToken);
                    if (!exprToken.empty()) {
                        PUSH_TOKEN(exprToken);
                        exprToken.clear();
                    }
                    if (isOpeningParenthesis(c)) {
                        setParsingState(state, PARSING_STATE_OPAQUE, exprToken);
                        size_t len = getClosingParenthesis(cstr, i);
                        if (len != std::string::npos) {
                            exprToken = expression.substr(i + 1, len);
                            setParsingState(state, PARSING_STATE_EXPRESSION, exprToken);
                            exprToken = utils::strTrim(exprToken);
                            if (!exprToken.empty()) {
                                PUSH_TOKEN_OPAQUE(exprToken);
                                exprToken.clear();
                            }
                            i++;
                            i += len;
                            i++;

                            continue;
                        } else {
                            throw std::invalid_argument("Malformed expression.");
                        }

                    } else {
                        setParsingState(state, PARSING_STATE_OPERATOR, exprToken);
                        exprToken += c;
                    }
                    break;

                case PARSING_STATE_OPERATOR:
                    if (isOpeningParenthesis(c)) {
                        exprToken = utils::strTrim(exprToken);
                        if (!exprToken.empty()) {
                            PUSH_TOKEN(exprToken);
                            exprToken.clear();
                        }
                        setParsingState(state, PARSING_STATE_OPAQUE, exprToken);
                        size_t len = getClosingParenthesis(cstr, i);
                        if (len != std::string::npos) {
                            exprToken = expression.substr(i + 1, len);
                            setParsingState(state, PARSING_STATE_EXPRESSION, exprToken);
                            exprToken = utils::strTrim(exprToken);
                            if (!exprToken.empty()) {
                                PUSH_TOKEN_OPAQUE(exprToken);
                                exprToken.clear();
                            }
                            i++;
                            i += len;
                            i++;

                            continue;
                        } else {
                            throw std::invalid_argument("Malformed expression.");
                        }
                    }
                    else {
                        exprToken += c;
                    }
                    break;
                default:
                    throw std::invalid_argument("Malformed expression: unhandled parsing state state.");
                    break;
            }
        }
        else {
            switch (state) {
                case PARSING_STATE_EXPRESSION:
                    exprToken += c;
                    break;
                case PARSING_STATE_OPERATOR:
                    setParsingState(state, PARSING_STATE_EXPRESSION, exprToken);
                    exprToken = utils::strTrim(exprToken);
                    if (!exprToken.empty()) {
                        PUSH_TOKEN(exprToken);
                        exprToken.clear();
                    }
                    exprToken += c;
                    break;
                default:
                    throw std::invalid_argument("Malformed expression: unhandled parsing state state.");
                    break;
            }
        }
        ++i;
    }
    exprToken = utils::strTrim(exprToken);
    if (!exprToken.empty()) {
        PUSH_TOKEN(exprToken);
        exprToken.clear();
    }
}
