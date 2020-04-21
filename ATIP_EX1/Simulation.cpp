#include <iostream>
#include <fstream>
#include <filesystem>
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
	portCodeToNumOfStopsMap_.clear();
	shipRoute_.clear();
}

void Simulation::initAlgorithms(std::filesystem::directory_entry travelEntry) {

	std::filesystem::path pathToShipPlan = travelEntry;
	std::filesystem::path pathToShipRoute = travelEntry;
	pathToShipPlan += InputFileConstants::nameOfShipPlanFile;
	pathToShipRoute += InputFileConstants::nameOfShipRouteFile;

	for (size_t i = 0; i < algorithmVector_.size(); i++) {

		Algorithm* currAlgorithm = algorithmVector_.at(i);
		WeightBalanceCalculator calculator = WeightBalanceCalculator();

		currAlgorithm->readShipPlan(pathToShipPlan.u8string());
		currAlgorithm->readShipRoute(pathToShipRoute.u8string());
		currAlgorithm->setWeightBalanceCalculator(calculator);
	}
}

void Simulation::startSimulation() {

	clearErrorsFile();
	clearResultsFile();

	if (std::filesystem::exists(pathToRootFolder_)) {

		if (std::filesystem::is_directory(pathToRootFolder_)) {

			int travelCount = 1;
			std::filesystem::directory_iterator rootFolderIterator(pathToRootFolder_);
			for (const auto& travelEntry : rootFolderIterator) {

				std::string traveResultsLine = "Results For Travel #" + travelCount;
				writeResultsLine(traveResultsLine);

				if (std::filesystem::is_directory(travelEntry)) {

					initAlgorithms(travelEntry);
					shipRoute_ = algorithmVector_.at(0)->getShipRoute();
					initPortCodeToNumOfStopsMap(shipRoute_);

					int algorithmCount = 1;
					for (auto algorithm : algorithmVector_) {

						for (auto port : shipRoute_) {

							int numOfStopsAlreadyMade = portCodeToNumOfStopsMap_[port];
							std::filesystem::path travelFolderPath = travelEntry;

							std::string travelFolderPathAsString = travelFolderPath.u8string();
							traveShipToPort(algorithm, travelFolderPathAsString, port, numOfStopsAlreadyMade);
						}

						std::string instrsPeformed = std::to_string(algorithm->getOperationsPerformed());
						std::string algorithmNum = std::to_string(algorithmCount);
						std::string algorithmResultsLine = "Algorithm #" + algorithmNum + " performed " + instrsPeformed + " instructions";
						writeResultsLine(algorithmResultsLine);

						algorithmCount += 1;
					}
				}

				travelCount += 1;
			}
		}
	}
	else std::cout << "ERROR: Root folder path invalid" << std::endl;
}


void Simulation::initPortCodeToNumOfStopsMap(std::vector<std::string> route) {

	for (size_t i = 0; i < route.size(); i++) {

		std::string currPortCode = route.at(i);
		if (portCodeToNumOfStopsMap_.find(currPortCode) == portCodeToNumOfStopsMap_.end()) {

			portCodeToNumOfStopsMap_[currPortCode] = 0;
		}
	}
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

	portCodeToNumOfStopsMap_[port] += 1;
}


void Simulation::writeLineToFile(std::string& line, std::string& path) {

	std::ofstream fout(path, std::ofstream::app);
	fout << line << "\n";
	fout.close();
}

void Simulation::writeResultsLine(std::string& line) {

	std::string pathToResultsFile = pathToRootFolder_ + "simulation.results";
	writeLineToFile(line, pathToResultsFile);
}

void Simulation::writeErrorsLine(std::string& line) {

	std::string pathToErrorssFile = pathToRootFolder_ + "simulation.errorss";
	writeLineToFile(line, pathToErrorssFile);
}

void Simulation::clearFile(std::string& path) {
	std::ofstream fout(path);
	fout.close();
}

void Simulation::clearResultsFile() {

	std::string pathToResultsFile = pathToRootFolder_ + "simulation.results";
	clearFile(pathToResultsFile);
}

void Simulation::clearErrorsFile() {

	std::string pathToErrorsFile = pathToRootFolder_ + "simulation.errors";
	clearFile(pathToErrorsFile);
}
