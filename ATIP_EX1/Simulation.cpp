#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sys/stat.h>
#include "Simulation.h"
#include "constants.h"
#include "WeightBalanceCalculator.h"

Simulation::Simulation(std::string& pathToRootFolder, std::vector<Algorithm*>& algorithms) : pathToRootFolder_(pathToRootFolder) {

	algorithmVector_ = algorithms;
}

Simulation::~Simulation() {

	for (auto algorithm : algorithmVector_) {

		delete algorithm;
	}
	algorithmVector_.clear();
}

void Simulation::initAlgorithms(std::string& travelEntry) {

	std::string pathToShipPlan = travelEntry + InputFileConstants::nameOfShipPlanFile;
	std::string pathToShipRoute = travelEntry + InputFileConstants::nameOfShipRouteFile;

	for (size_t i = 0; i < algorithmVector_.size(); i++) {

		Algorithm* currAlgorithm = algorithmVector_.at(i);
		WeightBalanceCalculator calculator = WeightBalanceCalculator();

		currAlgorithm->readShipPlan(pathToShipPlan);
		currAlgorithm->readShipRoute(pathToShipRoute);
		currAlgorithm->setWeightBalanceCalculator(calculator);
	}
}

void Simulation::startSimulation() {

	clearErrorsFile();
	clearResultsFile();

	if (IsPathExist(pathToRootFolder_)) {

		int travelCount = 1;

		std::string travelPath = pathToRootFolder_ + "/Travel_" + std::to_string(travelCount);
		while (IsPathExist(travelPath)) {

			std::string traveResultsLine = "Results For Travel #:" + std::to_string(travelCount) + "\n";
			writeResultsLine(traveResultsLine);

			std::string traveErrorsLine = "\nErrors For Travel #:" + std::to_string(travelCount) + "\n";
			std::cout << traveErrorsLine << std::endl;

			initAlgorithms(travelPath);

			int algorithmCount = 1;
			for (auto algorithm : algorithmVector_) {

				std::vector<std::string> shipRoute = algorithm->getShipRoute();
				std::map<std::string, int> portCodeToNumOfStopsMap = getPortCodeToNumOfStopsMap(shipRoute);

				std::string algorithmErrorLine = "\n\tAlgorithm #" + std::to_string(algorithmCount) + " encountered the following Errors:\n";
				std::cout << algorithmErrorLine << std::endl;

				for (auto port : shipRoute) {

					int numOfStopsAlreadyMade = portCodeToNumOfStopsMap[port];

					traveShipToPort(algorithm, travelPath, port, numOfStopsAlreadyMade);
					portCodeToNumOfStopsMap[port] += 1;
				}



				std::string instrsPeformed = std::to_string(algorithm->getOperationsPerformed());
				std::string algorithmNum = std::to_string(algorithmCount);

				std::string algorithmResultsLine = "\tAlgorithm #" + algorithmNum + " performed " + instrsPeformed + " instructions\n";
				writeResultsLine(algorithmResultsLine);

				algorithmCount += 1;
			}

			travelCount += 1;
			travelPath = pathToRootFolder_ + "/Travel_" + std::to_string(travelCount);
		}
	}
	else std::cout << "ERROR: Root folder path invalid" << std::endl;
}


std::map<std::string, int> Simulation::getPortCodeToNumOfStopsMap(std::vector<std::string>& route) {

	std::map<std::string, int> portCodeToNumOfStopsMap;
	for (auto port : route) {

		portCodeToNumOfStopsMap[port] = 0;
	}

	return portCodeToNumOfStopsMap;
}

void Simulation::traveShipToPort(Algorithm* algorithm, std::string& travelFolderPath, std::string& port, int numOfStopsAlreadyMade) {

	std::string cargoPath = travelFolderPath;
	std::string instrOutputPath = travelFolderPath;

	std::string numOfCurrStop = std::to_string(numOfStopsAlreadyMade + 1);
	std::string cargoFileName = "/" + port + "_" + numOfCurrStop + ".cargo_data";
	std::string outputFileName = "/" + port + "_" + numOfCurrStop + "_output.txt";

	cargoPath += cargoFileName;
	instrOutputPath += outputFileName;

	algorithm->getInstructionsForCargo(cargoPath, instrOutputPath);
}


void Simulation::writeLineToFile(std::string& line, std::string& path) {

	std::ofstream fout(path, std::ofstream::app);
	if (fout.is_open()) {
		fout << line << "\n";
	}

	fout.close();
}

void Simulation::writeResultsLine(std::string& line) {

	std::string pathToResultsFile = pathToRootFolder_ + "/simulation.results";
	writeLineToFile(line, pathToResultsFile);
}


void Simulation::clearFile(std::string& path) {
	std::ofstream fout(path);
	fout.close();
}

void Simulation::clearResultsFile() {

	std::string pathToResultsFile = pathToRootFolder_ + "/simulation.results";
	clearFile(pathToResultsFile);
}

void Simulation::clearErrorsFile() {

	std::string pathToErrorsFile = pathToRootFolder_ + "/simulation.errors";
	clearFile(pathToErrorsFile);
}


bool Simulation::IsPathExist(const std::string& path) {
	struct stat buffer;
	return (stat(path.c_str(), &buffer) == 0);
}