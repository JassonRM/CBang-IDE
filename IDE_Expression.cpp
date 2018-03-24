//
// Created by marco on 24/03/18.
//

#include "IDE_Expression.h"

bool IDE_Expression::isLeaf(){
    return internalExpressions.size() == 0;
}

void IDE_Expression::addExpression(IDE_Expression* newExpression){
    internalExpressions.push_back(newExpression);
}
