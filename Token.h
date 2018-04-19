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
    int line = 0;
    tokenType type;
    string value;
    static int lineNum;

    /**Crea un token según el valor indicado y asigna un tipo
     *
     * @param value
     */
    Token(string value);

    /**Crea un token según el valor indicado y el tipo indicado
     *
     * @param value
     * @param type
     */
    Token(string value,tokenType type);
private:
    tokenType evaluateToken(string);
};


#endif //CODEPARSER_TOKEN_H
