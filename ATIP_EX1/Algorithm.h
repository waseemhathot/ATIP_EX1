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
	void readShipPlan(const std::string& filePath);
	void readShipRoute(const std::string& filePath);
	void getInstructionsForCargo(const std::string& pathToInputCargoFile, const std::string& pathToOutputInstructionsFile);

private:
	std::vector<std::vector<std::string>> readPortCargo(const std::string& filePath);
	void writeLinesToFile(const std::string& filePath, std::vector<std::string> lines)
};

#endif