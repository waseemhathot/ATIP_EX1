#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include "constants.h"
#include "Algorithm.h"


Algorithm::Algorithm() {
	shipPlan_ = NULL;
}

Algorithm::~Algorithm() {
	
	delete shipPlan_;
}

bool Algorithm::isLineFormatValid(std::string line, std::regex reg) {
	if (!(std::regex_match(line, reg))) {
		return false;
	}

	return true;
}

std::vector<std::string> Algorithm::getTokensFromLineIntoVector(std::string& line) {
	std::vector<std::string> lineTokensVector;
	std::smatch stringMatch;
	std::regex tokensInlineRegex(InputFileConstants::getTokensInLineRegexstring);

	std::string currentString = line;
	while (std::regex_search(currentString, stringMatch, tokensInlineRegex)) {

		lineTokensVector.push_back(stringMatch[0]);
		currentString = stringMatch.suffix();
	}

	return lineTokensVector;
}

std::vector<std::vector<std::string>> Algorithm::readFileByLineIntoVector(const std::string& filePath, std::regex reg) {

	std::string line;
	std::ifstream fin(filePath);
	std::vector<std::vector<std::string>> result;

	if (fin.is_open()) {

		while (std::getline(fin, line)) {

			std::vector<std::string> tokensInLine;
			if (isLineFormatValid(line, reg)) {

				tokensInLine = getTokensFromLineIntoVector(line);
				result.push_back(tokensInLine);
			}
			else {
				std::cout << "WARNING! Bad input: " << line << std::endl;
			}
		}

		fin.close();
		return result;
	}
	else std::cout << "Unable to open file";

	return result;
}


void Algorithm::readShipRoute(const std::string& filePath) {

	std::vector<std::string> shipRoute;
	const std::regex shipRouteRegex(InputFileConstants::shipRouteRegexString);
	std::vector<std::vector<std::string>> fileLinesInVector = readFileByLineIntoVector(filePath, shipRouteRegex);

	for (size_t i = 0; i < fileLinesInVector.size(); ++i) {

		shipRoute.push_back(fileLinesInVector.at(i).at(0));
	}
	
	shipRoute_ = shipRoute;
}

void Algorithm::readShipPlan(const std::string& filePath) {

	std::vector<std::vector<int>> shipPlan;
	const std::regex shipPlanRegex(InputFileConstants::shipPlanRegexString);

	std::vector<std::vector<std::string>> fileLinesInVector = readFileByLineIntoVector(filePath, shipPlanRegex);

	if (!fileLinesInVector.empty()) {

		int numFloors = stoi(fileLinesInVector.at(0).at(0));
		int numContainersInX = stoi(fileLinesInVector.at(0).at(1));
		int numContainersInY = stoi(fileLinesInVector.at(0).at(2));

		std::vector<int> firstLine = { numFloors, numContainersInX, numContainersInY };
		shipPlan.push_back(firstLine);

		std::vector<int> planLine;
		for (size_t i = 1; i < fileLinesInVector.size(); ++i) {

			int posX = stoi(fileLinesInVector.at(i).at(0));
			int posY = stoi(fileLinesInVector.at(i).at(1));
			int actualNumOfFloors = stoi(fileLinesInVector.at(i).at(2));

			if (posX <= numContainersInX && posX >= 0 && posY <= numContainersInY && posY >= 0 && actualNumOfFloors < numFloors
				&& actualNumOfFloors >= 0) {

				planLine = { posX, posY, actualNumOfFloors };
				shipPlan.push_back(planLine);
			}
		}
	}

	shipPlan_ = new ShipPlan(shipPlan);
}

vector<vector<string>> Algorithm::readPortCargo(const std::string& filePath) {

	vector<vector<string>> portCargo;
	const std::regex portCargoRegex(InputFileConstants::portCargoRegexString);

	vector<vector<string>> fileLinesInVector = readFileByLineIntoVector(filePath, portCargoRegex);

	return fileLinesInVector;
}

void Algorithm::writeLinesToFile(const std::string& filePath, std::vector<std::string> lines) {

	std::ofstream fout(filePath);
	for (size_t i = 0; i < lines.size(); i++) {
		fout << lines.at(i) << "\n";
	}

	fout.close();
}

void Algorithm::getInstructionsForCargo(const std::string& pathToInputCargoFile, const std::string& pathToOutputInstructionsFile) {

	std::vector<Container*> containersToLoad;
	std::vector<string> instructionLines;
	std::vector<std::vector<std::string>> cargoData = readPortCargo(pathToInputCargoFile);

	Container* currContainer;
	for (size_t i = 0; i < cargoData.size(); i++) {

		string containerId = cargoData.at(i).at(0);
		int containerWeight = stoi(cargoData.at(i).at(1));
		string destCode = cargoData.at(i).at(2);
		currContainer = new Container(containerWeight, destCode, containerId);
		containersToLoad.push_back(currContainer);
	}
}



