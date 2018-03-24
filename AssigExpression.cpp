//
// Created by marco on 24/03/18.
//

#include "AssigExpression.h"

void AssigExpression::interpret() {
    if (isLeaf()) {
        //Assign value to memory slot
        return;
    }
    int end = internalExpressions.size();
    for (int begin = 0; begin < end; begin++) {
        (internalExpressions)[begin]->interpret();
    }

    //Assign value to memory slot
}