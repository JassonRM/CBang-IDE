//
// Created by marco on 28/03/18.
//

#ifndef CODEPARSER_PARSER_H
#define CODEPARSER_PARSER_H

#include <iostream>
#include <vector>
#include "Token.h"
#include "Variable.h"
#include <boost/tokenizer.hpp>
#include <QJsonObject>

using namespace std;

static int currentScope = 0;

void parse(string);
void parse(vector<Token*>*);
vector<Token*>* lex(string);


#endif //CODEPARSER_PARSER_H
