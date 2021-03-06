#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include "constants.h"
#include "Algorithm.h"


Algorithm::Algorithm() : portIndex_(0), shipPlan_(NULL), operationsPerformed_(0) {}

Algorithm::~Algorithm() {

	delete shipPlan_;
}

void Algorithm::setWeightBalanceCalculator(WeightBalanceCalculator& calc) {

	calculator_ = calc;
}

bool Algorithm::isLineFormatValid(std::string& line, std::regex reg) {
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
				std::cout << "\tERROR! Bad input: " << line << std::endl;
			}
		}

		fin.close();
		return result;
	}
	else std::cout << "\tERROR! Unable to open file: " << filePath << std::endl;

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

	operationsPerformed_ = 0;
	std::vector<std::vector<int>> shipPlan;
	const std::regex shipPlanRegex(InputFileConstants::shipPlanRegexString);

	std::vector<std::vector<std::string>> fileLinesInVector = readFileByLineIntoVector(filePath, shipPlanRegex);

	if (!fileLinesInVector.empty()) {

		int numFloors = stoi(fileLinesInVector.at(0).at(0));
		int numContainersInX = stoi(fileLinesInVector.at(0).at(1));
		int numContainersInY = stoi(fileLinesInVector.at(0).at(2));

		std::vector<int> firstLine = { numFloors, numContainersInX, numContainersInY };
		shipPlan.push_back(firstLine);

		for (size_t i = 1; i < fileLinesInVector.size(); ++i) {

			int posX = stoi(fileLinesInVector.at(i).at(0));
			int posY = stoi(fileLinesInVector.at(i).at(1));
			int actualNumOfFloors = stoi(fileLinesInVector.at(i).at(2));

			if (posX <= numContainersInX && posX >= 0 && posY <= numContainersInY && posY >= 0 && actualNumOfFloors < numFloors
				&& actualNumOfFloors >= 0) {

				std::vector<int> planLine = { posX, posY, actualNumOfFloors };
				shipPlan.push_back(planLine);
			}
		}

		if (shipPlan_ == NULL) {

			shipPlan_ = new ShipPlan(shipPlan);
		}
		else {

			delete shipPlan_;
			shipPlan_ = new ShipPlan(shipPlan);
		}

	}
}

std::vector<std::vector<std::string>> Algorithm::readPortCargo(const std::string& filePath) {

	std::vector<std::vector<std::string>> portCargo;
	const std::regex portCargoRegex(InputFileConstants::portCargoRegexString);

	std::vector<std::vector<std::string>> fileLinesInVector = readFileByLineIntoVector(filePath, portCargoRegex);

	return fileLinesInVector;
}

void Algorithm::writeLinesToFile(const std::string& filePath, std::vector<std::string>& lines) {

	std::ofstream fout(filePath, std::ofstream::app);

	if (fout.is_open()) {

		for (size_t i = 0; i < lines.size(); i++) {
			fout << lines.at(i) << "\n";
		}
	}
	else std::cout << "\tERROR: Unable to open file" << std::endl;

	fout.close();
}

void Algorithm::getInstructionsForCargo(const std::string& pathToInputCargoFile, const std::string& pathToOutputInstructionsFile) {

	clearOutputFile(pathToOutputInstructionsFile);

	if (portIndex_ == shipRoute_.size() - 1) {

		unloadAllContainers(pathToOutputInstructionsFile);
		portIndex_ = 0;
		return;
	}

	std::vector<std::string> instructionLines;

	std::string currPortCode = shipRoute_.at(portIndex_);
	std::vector<std::vector<std::string>> cargoData = readPortCargo(pathToInputCargoFile);
	std::vector<Container*> containersToLoad = getContainersToLoadForCargo(cargoData);

	std::vector<std::vector<std::string>> instructionsToUnloadFromShipToPort = shipPlan_->getInstructionsForUnloadAtPort(currPortCode);
	std::vector<Container*> unloadedContainers = unloadContainersAtPort(instructionsToUnloadFromShipToPort, pathToOutputInstructionsFile);

	for (size_t i = 0; i < unloadedContainers.size(); i++) {

		Container* currContainer = unloadedContainers.at(i);
		if (currContainer->getDestCode() == currPortCode) {

			delete currContainer;
		}
		else {

			containersToLoad.push_back(currContainer);
		}
	}

	loadContainers(containersToLoad, pathToOutputInstructionsFile);
	portIndex_ += 1;
}


std::vector<std::vector<std::string>> Algorithm::getInstructionsForUnloadAtPort(std::string& portCode) {

	std::vector<std::vector<std::string>> instructions = shipPlan_->getInstructionsForUnloadAtPort(portCode);
	return instructions;
}

std::vector<Container*> Algorithm::getContainersToLoadForCargo(std::vector<std::vector<std::string>>& cargoData) {

	std::vector<Container*> containersToLoad;
	for (size_t i = 0; i < cargoData.size(); i++) {

		std::string containerId = cargoData.at(i).at(0);
		int containerWeight = stoi(cargoData.at(i).at(1));
		std::string destCode = cargoData.at(i).at(2);
		Container* currContainer = new Container(containerWeight, destCode, containerId);
		containersToLoad.push_back(currContainer);
	}

	return containersToLoad;
}

std::vector<Container*> Algorithm::unloadContainersAtPort(std::vector<std::vector<std::string>>& unloadInstructions, const std::string& outputFilePath) {

	std::vector<Container*> unloadedContainers;
	std::vector<std::string> instructionLines;

	for (size_t i = 0; i < unloadInstructions.size(); i++) {

		std::string floor = unloadInstructions.at(i).at(1);
		std::string xPos = unloadInstructions.at(i).at(2);
		std::string yPos = unloadInstructions.at(i).at(3);
		Container* currContainer = shipPlan_->unloadContainer(stoi(xPos), stoi(yPos));
		std::string currInstructionLine = "U, " + currContainer->getContainerId() + ", " + floor + ", " + xPos + ", " + yPos;

		instructionLines.push_back(currInstructionLine);
		unloadedContainers.push_back(currContainer);
		operationsPerformed_ += 1;
	}

	writeLinesToFile(outputFilePath, instructionLines);
	return unloadedContainers;
}


std::vector<int> Algorithm::findSpaceToLoad() { //returns <floor, xpos, ypos>

	std::vector<int> location = shipPlan_->findSpaceToLoad();
	return location;
}


void Algorithm::loadContainers(std::vector<Container*>& containers, const std::string& outputFilePath) {

	std::vector<std::string> instructionLines;
	for (size_t i = 0; i < containers.size(); i++) {

		Container* currContainer = containers.at(i);
		std::string containerId = currContainer->getContainerId();
		std::string destPort = currContainer->getDestCode();

		if (!checkIfPortIsInRoute(destPort)) {
			std::cout << "\tERROR: destination is not on route, failed to load container with id " << containerId << std::endl;
			continue;
		}

		std::vector<int> foundLocation = findSpaceToLoad();
		if (foundLocation.empty()) {
			std::cout << "\tERROR: Ship is full, failed to load container with id " << containerId << std::endl;
			continue;
		}

		int floor = foundLocation.at(0);
		int xPos = foundLocation.at(1);
		int yPos = foundLocation.at(2);


		shipPlan_->loadContainer(currContainer, floor, xPos, yPos);
		std::string currInstructionLine = "L, " + containerId + ", " + std::to_string(floor) + ", " + std::to_string(xPos) + ", " + std::to_string(yPos);
		instructionLines.push_back(currInstructionLine);
		operationsPerformed_ += 1;
	}

	writeLinesToFile(outputFilePath, instructionLines);
}

std::vector<std::string> Algorithm::getShipRoute() {

	return shipRoute_;
}


void Algorithm::unloadAllContainers(const std::string& pathToOutputInstructionsFile) {

	std::vector<std::vector<std::string>> instructionsToUnloadFromShipToPort = shipPlan_->getInstructionsToUnloadAll();
	std::vector<Container*> unloadedContainers = unloadContainersAtPort(instructionsToUnloadFromShipToPort, pathToOutputInstructionsFile);

	for (auto container : unloadedContainers) {

		delete container;
	}
}


void Algorithm::clearOutputFile(const std::string& path) {

	std::ofstream fout(path);
	if (fout.is_open()) {

		fout.close();
	}
}

int Algorithm::getOperationsPerformed() {

	return operationsPerformed_;
}

bool Algorithm::checkIfPortIsInRoute(std::string& currPort) {

	bool res = false;
	for (auto port : shipRoute_) {

		if (currPort == port) {
			res = true;
			break;
		}
	}

	return res;
}