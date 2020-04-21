#include <iostream>
#include "WeightBalanceCalculator.h"


WeightBalanceCalculator::WeightBalanceCalculator() {}

WeightBalanceCalculator::~WeightBalanceCalculator() {}

BalanceStatus WeightBalanceCalculator::tryOperation(char loadUnload, int kg, int X, int Y) {

	return BalanceStatus::APPROVED;
}