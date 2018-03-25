//
// Created by marco on 24/03/18.
//

#include "ScopeExpression.h"


void ScopeExpression::interpret() {
    if (isLeaf()){
        return;
    }
    int end = internalExpressions.size();
    for (int begin = 0; begin < end; begin++){
        (internalExpressions)[begin]->interpret();
    }
}