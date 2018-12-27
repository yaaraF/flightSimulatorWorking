
#ifndef SIMULATORFLIGHT_DIV_H
#define SIMULATORFLIGHT_DIV_H

#include "BinaryExpression.h"

class Div : public BinaryExpression {
public:
    Div(Expression *rightexp, Expression *leftExp) : BinaryExpression(rightexp, leftExp) {};

    double calculate();

    void setParm(vector<string> s) {}

};

#endif //SIMULATORFLIGHT_DIV_H
