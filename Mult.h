//
// Created by yaara on 12/13/18.
//

#ifndef SIMULATORFLIGHT_MULT_H
#define SIMULATORFLIGHT_MULT_H

#include "BinaryExpression.h"

class Mult : public BinaryExpression {
public:
    Mult(Expression* rightexp,Expression* leftExp):BinaryExpression(rightexp,leftExp){};
    double calculate();

    void setParm(vector<string>s){}

};


#endif //SIMULATORFLIGHT_MULT_H
