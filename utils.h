//
// Created by Makram.Elghazzaoui on 27/04/2023.
//

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <string>
#include <sstream>

namespace utils {

#define DECLARE_STR_TO_TYPE(TYPE, FCTNAME) TYPE FCTNAME(const std::string& s);

    DECLARE_STR_TO_TYPE(double, strToDoule)

    DECLARE_STR_TO_TYPE(long double, strToLongDoule)

    DECLARE_STR_TO_TYPE(int, strToInt)

    DECLARE_STR_TO_TYPE(unsigned int, strToUnsigned)


    bool isAlpha(char c);

    bool isNum(char c);

    bool isAlphaNum(char c);
}

#endif //TEST_UTILS_H
