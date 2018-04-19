//
// Created by marco on 27/03/18.
//
#include "Token.h"

int Token::lineNum = 1;

tokenType Token::evaluateToken(string token){
    char types[][7] = {"int","char","long","double","float"};
    for (char* type : types) {
        string stringType(type);
        if ( stringType == token){
            return DATA_TYPE;
        }
    }
    if(token == "="){
        return ASSIGNMENT;
    }
    else if(token == ";"){
        return LINE_SEPARATOR;
    }
    else if(token == "\n") {
        lineNum++;
        return END_LINE;
    }else if(token == "{"){
        return OPEN_SCOPE;
    }else if(token == "}") {
        return CLOSE_SCOPE;
    }else if(token == "reference"){
        return REFERENCE;
    }else if(token == "<"){
        return OPEN_REFERENCE_SEPARATOR;
    }else if(token == ">") {
        return CLOSE_REFERENCE_SEPARATOR;
    }else if (token == "struct") {
        return STRUCT;
    }else if(token == "getAddr") {
        return ADDRESS;
    }else if(token == "getValue") {
        return VALUE;
    }else if(token == "print"){
        return PRINT;
    }else if(token == "\t"){
        return END_LINE;
        //TODO fix
    }else {

        regex regexIdentifier("[_a-zA-Z][_a-zA-Z0-9]*");
        if (regex_match(token, regexIdentifier)){
            return IDENTIFIER;
        }
        regex regex("\'[A-Za-z]\'");
        if (regex_match(token,regex)){
            return LITERAL;
        }

        char arithmeticOperators[][2] = {"+","-","*","/","%","(",")"};
        for (char* arithmeticOperator:arithmeticOperators) {
            string stringOperator(arithmeticOperator);
            if (token == arithmeticOperator ){
                return OPERATOR;
            }
        }
        return LITERAL;

    }
}

Token::Token(string value){
    this->value = value;
    this->type = evaluateToken(value);
    this->line = lineNum;
}

Token::Token(string value,tokenType type) {
    this->value = value;
    this->type = type;
    this->line = -1;
}
