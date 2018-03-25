//
// Created by marco on 25/03/18.
//

#include "DeclarationExpression.h"

void DeclarationExpression::interpret() {
    if (isLeaf()) {
        //Create memory slot
        return;
    }
    int end = internalExpressions.size();
    for (int begin = 0; begin < end; begin++) {
        (internalExpressions)[begin]->interpret();
    }

    //create memory slot
}