//
// Created by Makram.Elghazzaoui on 27/04/2023.
//
#include "utils.h"

namespace utils {

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

    bool isWhiteSpace(char c) {
        return  c == ' ' ||
                c == '\t' ||
                c == '\r' ||
                c == '\n';
    }

    std::string strTrim(const std::string& s) {
        const char* cstr = s.c_str();
        size_t offsetBegin = 0;
        while(isWhiteSpace(cstr[offsetBegin])) {
            offsetBegin++;
        }
        size_t offsetEnd = s.size();
        while(isWhiteSpace(cstr[offsetEnd-1])) {
            offsetEnd--;
        }
        if (offsetBegin > 0 || offsetEnd != s.size()) {
            return s.substr(offsetBegin, offsetEnd-offsetBegin);
        }

        return s;
    }
}
