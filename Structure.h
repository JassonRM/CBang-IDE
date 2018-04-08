//
// Created by marco on 07/04/18.
//

#ifndef CFACTORIAL_IDE_STRUCTURE_H
#define CFACTORIAL_IDE_STRUCTURE_H


#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include "Variable.h"

class Structure {

    QJsonArray* variables = new QJsonArray;
    QJsonObject* json = new QJsonObject;

public:
    void add(Variable* var);
    void put(string,string);
    void submit();
    string toString();
};


#endif //CFACTORIAL_IDE_STRUCTURE_H
