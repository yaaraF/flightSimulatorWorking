
#include "Plus.h"

double Plus::calculate() {
    return this->leftExp->calculate()+this->rightExp->calculate();
}