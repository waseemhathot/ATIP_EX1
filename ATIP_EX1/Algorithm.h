#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "ShipPlan.h"

#ifndef ALGORITHM_H
#define ALGORITHM_H

class Algorithm {

	ShipPlan* shipPlan_;
	std::vector<std::string> shipRoute_;

public:
	Algorithm();
	~Algorithm();
	
	bool isLineFormatValid(std::string line, std::regex reg);
	std::vector<std::string> getTokensFromLineIntoVector(std::string& line);
	std::vector<std::vector<std::string>> readFileByLineIntoVector(const std::string& filename, std::regex reg);
	void readShipPlan(std::string& filePath);
	void readShipRoute(std::string& filePath);
};

#endif