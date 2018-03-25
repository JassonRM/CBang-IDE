//
// Created by marco on 25/03/18.
//

#include "ArithmeticExpression.h"

void ArithmeticExpression::interpret() {
    if (isLeaf()) {
        //Solve arithmetic expression
        return;
    }
    int end = internalExpressions.size();
    for (int begin = 0; begin < end; begin++) {
        (internalExpressions)[begin]->interpret();
    }

    //Solve arithmetic expression
}