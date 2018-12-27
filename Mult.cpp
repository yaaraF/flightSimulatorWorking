
#include "Mult.h"

double Mult::calculate() {
    return this->leftExp->calculate()*this->rightExp->calculate();
}