

#ifndef SIMULATORFLIGHT_NUMBER_H
#define SIMULATORFLIGHT_NUMBER_H

#include "Expression.h"

class Number : public Expression {
    double value;
public:
    Number(double value);
    double calculate();
    void setParm(vector<string>s){

    }


};

#endif //SIMULATORFLIGHT_NUMBER_H
