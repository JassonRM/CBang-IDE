//
// Created by marco on 24/03/18.
//

#ifndef CFACTORIAL_IDE_IDE_EXPRESSION_H
#define CFACTORIAL_IDE_IDE_EXPRESSION_H

#include <vector>

class IDE_Expression {

protected:
    std::vector<IDE_Expression*> internalExpressions = nullptr;

public:

    virtual void interpret();

    bool isLeaf();

    void addExpression(IDE_Expression*);

};

#endif //CFACTORIAL_IDE_IDE_EXPRESSION_H
