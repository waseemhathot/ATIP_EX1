#include <iostream>
#include "constants.h"




#ifndef WEIGHT_BALANCE_CALCULATOR_H
#define WEIGHT_BALANCE_CALCULATOR_H


enum class BalanceStatus { APPROVED, X_IMBALANCED, Y_IMBALANCED, X_Y_IMBALANCED };

class WeightBalanceCalculator {


public:
	WeightBalanceCalculator();
	~WeightBalanceCalculator();

	BalanceStatus tryOperation(char loadUnload, int kg, int X, int Y);
};

#endif