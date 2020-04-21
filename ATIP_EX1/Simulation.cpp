#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include "Simulation.h"
#include "constants.h"


Simulation::Simulation(std::string& pathToRootFolder, std::vector<Algorithm*>& algorithms): pathToRootFolder_(pathToRootFolder) {
	
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

void Simulation::startSimulation() {

	if (std::filesystem::exists(pathToRootFolder_)) {

		if (std::filesystem::is_directory(pathToRootFolder_)) {

			std::filesystem::directory_iterator rootFolderIterator(pathToRootFolder_);
			for (const auto& travelEntry : rootFolderIterator) {

				if (std::filesystem::is_directory(travelEntry)) {

					std::filesystem::path pathToShipPlan = travelEntry;
					std::filesystem::path pathToShipRoute = travelEntry;
					pathToShipPlan += InputFileConstants::nameOfShipPlanFile;
					pathToShipRoute += InputFileConstants::nameOfShipRouteFile;

					for (size_t i = 0; i < algorithmVector_.size(); i++) {

						Algorithm* currAlgorithm = algorithmVector_.at(i);
						currAlgorithm->readShipPlan(pathToShipPlan.u8string());
						currAlgorithm->readShipRoute(pathToShipRoute.u8string());
					}

					shipRoute_ = algorithmVector_.at(0)->getShipRoute();
					initPortCodeToNumOfStopsMap(shipRoute_);

					for (auto algorithm : algorithmVector_) {

						for (auto port : shipRoute_) {

							int numOfStopsAlreadyMade = portCodeToNumOfStopsMap_[port];
							std::filesystem::path travelFolderPath = travelEntry;

							std::string travelFolderPathAsString = travelFolderPath.u8string();
							traveShipToPort(algorithm, travelFolderPathAsString, port, numOfStopsAlreadyMade);
						}
					}
				}
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

