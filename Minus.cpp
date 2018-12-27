

#include "Minus.h"

double Minus::calculate() {
    return this->leftExp->calculate()-this->rightExp->calculate();
}
