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
	int portIndex_;

public:
	Algorithm();
	~Algorithm();


	void readShipPlan(const std::string& filePath);
	void readShipRoute(const std::string& filePath);
	std::vector<std::string> getShipRoute();
	void getInstructionsForCargo(const std::string& pathToInputCargoFile, const std::string& pathToOutputInstructionsFile);
	void unloadAllContainers(const std::string& pathToOutputInstructionsFile);

private:
	bool isLineFormatValid(std::string& line, std::regex reg);
	std::vector<std::string> getTokensFromLineIntoVector(std::string& line);
	std::vector<std::vector<std::string>> readFileByLineIntoVector(const std::string& filename, std::regex reg);
	std::vector<std::vector<std::string>> readPortCargo(const std::string& filePath);
	void writeLinesToFile(const std::string& filePath, std::vector<std::string>& lines);
	std::vector<int> findSpaceToLoad();
	std::vector<std::vector<std::string>> getInstructionsForUnloadAtPort(std::string& portCode);
	std::vector<Container*> getContainersToLoadForCargo(std::vector<std::vector<std::string>>& cargoData);
	std::vector<Container*> unloadContainersAtPort(std::vector<std::vector<std::string>>& unloadInstructions, const std::string& outputFilePath);
	void loadContainers(std::vector<Container*>& containers, const std::string& outputFilePath);
	void clearOutputFile(const std::string& path);
};

#endif