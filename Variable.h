//
// Created by marco on 27/03/18.
//

#ifndef CODEPARSER_VARIABLE_H
#define CODEPARSER_VARIABLE_H

#include <iostream>
#include <vector>
#include <QtCore/QJsonObject>
#include "Token.h"
#include <QtCore/QJsonDocument>

using namespace std;

class Variable {
private:
    QJsonObject* json = new QJsonObject();

public:
    void put(string,string);

    void put(string,int);

    void put(string,char);

    void put(string,long);

    void put(string,double);

    void addValue(string value, Token* token);

    QJsonObject* get();

    string get(string);

    string toString();


};

#endif //CODEPARSER_VARIABLE_H
