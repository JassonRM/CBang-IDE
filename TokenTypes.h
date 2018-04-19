//
// Created by marco on 27/03/18.
//

#ifndef CODEPARSER_TOKENTYPE_H
#define CODEPARSER_TOKENTYPE_H

enum tokenType {
    IDENTIFIER = 2,
    OPERATOR = 3, // + - * / %
    LITERAL = 5, // 0-9 'a-z'
    LINE_SEPARATOR = 7, // ;
    OPEN_SCOPE = 11, // {
    CLOSE_SCOPE = 13, // }
    DATA_TYPE = 17, // int long char double float
    END_LINE = 19, // \n
    ASSIGNMENT = 23, // =
    STRUCT = 29, // struct
    REFERENCE = 31, // reference
    OPEN_REFERENCE_SEPARATOR = 37, // <
    CLOSE_REFERENCE_SEPARATOR = 41, // >
    ADDRESS = 43,// getAddr
    VALUE = 47,//getValue
    PRINT = 53//print

};

#endif //CODEPARSER_TOKENTYPE_H
