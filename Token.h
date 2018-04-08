//
// Created by marco on 27/03/18.
//

#ifndef CODEPARSER_TOKEN_H
#define CODEPARSER_TOKEN_H

#include <iostream>
#include "TokenTypes.h"
#include <boost/lexical_cast.hpp>
#include <regex>

using namespace std;

struct Token {
public:
    tokenType type;
    string value;

    Token(string value);

};

#endif //CODEPARSER_TOKEN_H
