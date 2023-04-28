//
// Created by Makram.Elghazzaoui on 27/04/2023.
//
#include "utils.h"

#define IMPLEMENT_STR_TO_TYPE(TYPE, FCTNAME) \
TYPE FCTNAME(const std::string& s) { \
TYPE x; \
std::istringstream iss(s); \
iss >> x; \
return x; \
}

IMPLEMENT_STR_TO_TYPE(double, strToDoule)
IMPLEMENT_STR_TO_TYPE(long double, strToLongDoule)
IMPLEMENT_STR_TO_TYPE(int, strToInt)
IMPLEMENT_STR_TO_TYPE(unsigned int, strToUnsigned)


bool isAlpha(char c) {
    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') || (c == '_');
}

bool isNum(char c) {
    return ('0' <= c && c <= '9') || (c == '.');
}

bool isAlphaNum(char c) {
    return isAlpha(c) || isNum(c);
}
