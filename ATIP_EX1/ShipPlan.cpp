#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include "file_IO.h"
#include "ShipPlan.h"

using std::vector;
using std::string;
using Route = std::vector<string>;



ShipPlanColumn::ShipPlanColumn(int columnCapacity, int xPos, int yPos) :
	columnCapacity_(columnCapacity),
	numOfContainersInColumn_(0),
	yPos_(yPos),
	xPos_(xPos)
{}

int ShipPlanColumn::loadContainer(Container* container) {

	if (containers_.size() == columnCapacity_) {

		return EXIT_FAILURE;
	}
	containers_.push_back(container);
	numOfContainersInColumn_ += 1;

	return EXIT_SUCCESS;
}

void ShipPlanColumn::setColumnCapacity(int capacity) {

	columnCapacity_ = capacity;
}

int ShipPlanColumn::getCapacity() {

	return columnCapacity_;
}

int ShipPlanColumn::getNumOfContainers() {

	return numOfContainersInColumn_;
}

bool ShipPlanColumn::isThereSpaceAvailable() {

	if (numOfContainersInColumn_ != columnCapacity_) {

		return true;
	}
	return false;
}

std::pair<int, int> ShipPlanColumn::getPos() {

	return std::make_pair(xPos_, yPos_);
}

vector<string> ShipPlanColumn::getInstructionsToUnloadContainer(string& portCode, int numOfContainersToUnloadForPort) {

	vector<string> instructions;
	string currInstruction;
	vector<string> loadBackInstructions;
	int containersToUnloadFound = 0;
	for (size_t i = containers_.size() - 1; i >= 0 && containersToUnloadFound < numOfContainersToUnloadForPort; i--) {

		string currContainerId = containers_.at(i)->getContainerId();
		string currContainerPortCode = containers_.at(i)->getDestCode();

		currInstruction = "U, " + currContainerId + ", " + std::to_string(i) + ", " + std::to_string(xPos_) + ", " + std::to_string(yPos_);
		instructions.push_back(currInstruction);

		if (portCode == currContainerPortCode) {

			containersToUnloadFound += 1;
		}
		else {

			
			currInstruction = "L, " + currContainerId + ", " + std::to_string(i) + ", " + std::to_string(xPos_) + ", " + std::to_string(yPos_);
			loadBackInstructions.push_back(currInstruction);
		}
	}

	instructions.insert(instructions.end(), loadBackInstructions.begin(), loadBackInstructions.end());

	return instructions;
}




ShipPlan::ShipPlan(vector<vector<int>> shipPlanData) : numOfContainersOnShip_(0) {

	numOfFloors_ = shipPlanData.at(0).at(0);
	containersInXDim_ = shipPlanData.at(0).at(1);
	containersInYDim_ = shipPlanData.at(0).at(2);
	shipCapacity_ = (containersInXDim_ * containersInYDim_) * numOfFloors_;

	for (int i = 0; i < containersInXDim_; i++) {
		for (int j = 0; j < containersInYDim_; j++) {

			ShipPlanColumn* planColumn = new ShipPlanColumn(numOfFloors_, i, j);
			std::pair<int, int> columnPos = std::make_pair(i, j);
			this->plan_[columnPos] = planColumn;
		}
	}

	for (size_t i = 1; i < shipPlanData.size(); i++) {

		int xPos = shipPlanData.at(i).at(0);
		int yPos = shipPlanData.at(i).at(1);
		int actualNumOfFloors = shipPlanData.at(i).at(2);
		std::pair<int, int> pos = std::make_pair(xPos, yPos);

		ShipPlanColumn* column = plan_[pos];
		column->setColumnCapacity(actualNumOfFloors);

		shipCapacity_ = shipCapacity_ - (numOfFloors_ - actualNumOfFloors);
	}
}

int ShipPlan::getCapacityOfColumn(int xPos, int yPos) {

	std::pair<int, int> pos = std::make_pair(xPos, yPos);
	ShipPlanColumn* column = plan_[pos];
	int capacity = column->getCapacity();

	return capacity;
}

int ShipPlan::getNumOfContainersInColumn(int xPos, int yPos) {

	std::pair<int, int> pos = std::make_pair(xPos, yPos);
	ShipPlanColumn* column = plan_[pos];
	int numOfContainers = column->getNumOfContainers();

	return numOfContainers;
}

int ShipPlan::getShipCapacity() {

	return shipCapacity_;
}

void ShipPlan::loadContainer(Container* container) {

	std::map<std::pair<int, int>, ShipPlanColumn*>::iterator it = plan_.begin();
	bool isContainerLoaded = false;
	string containerId = container->getContainerId();
	string containerDestPort = container->getDestCode();

	while (!isContainerLoaded && it != plan_.end()) {

		ShipPlanColumn* column = it->second;
		if (column->isThereSpaceAvailable()) {

			column->loadContainer(container);
			containersToColumnMap_[container->getContainerId()] = column;

			if (portsToContainersIdMap_.find(containerDestPort) != portsToContainersIdMap_.end()) {

				portsToContainersIdMap_[containerDestPort].push_back(containerId);
			}

			else {

				vector<string> containerIds;
				containerIds.push_back(containerId);
				portsToContainersIdMap_[containerDestPort] = containerIds;
			}

			isContainerLoaded = true;
		}

		it++;
	}
}

vector<string> ShipPlan::getInstructionsForUnloadAsVector(string& portCode) {

	vector<string> idsOfContainersToBeUnloaded = portsToContainersIdMap_[portCode];
	vector<string> instructions;

	std::map<std::pair<int, int>, int> colToNumOfContainersMap = createColumnToNumOfContainersToUnloadByPortMap(idsOfContainersToBeUnloaded);

	std::map<std::pair<int, int>, int>::iterator it = colToNumOfContainersMap.begin();
	vector<string> instrForCurrColumn;
	while (it != colToNumOfContainersMap.end()) {

		ShipPlanColumn* currColumn = plan_[it->first];
		int numOfContainersToUnload = it->second;

		instrForCurrColumn = currColumn->getInstructionsToUnloadContainer(portCode, numOfContainersToUnload);
		instructions.insert(instructions.end(), instrForCurrColumn.begin(), instrForCurrColumn.end());

		it++;
	}

	return instructions;
}

std::map<std::pair<int, int>, int> ShipPlan::createColumnToNumOfContainersToUnloadByPortMap(vector<string> idsOfContainersToUnload) {

	std::map<std::pair<int, int>, int> columnToNumOfContainersToUnloadByPortMap;
	for (size_t i = 0; i < idsOfContainersToUnload.size(); i++) {

		ShipPlanColumn* columnOfTheContainer = containersToColumnMap_[idsOfContainersToUnload.at(i)];
		std::pair<int, int> columnPos = columnOfTheContainer->getPos();

		if (columnToNumOfContainersToUnloadByPortMap.find(columnPos) != columnToNumOfContainersToUnloadByPortMap.end()) {

			columnToNumOfContainersToUnloadByPortMap[columnPos] += 1;
		}
		else {

			columnToNumOfContainersToUnloadByPortMap[columnPos] = 1;
		}
	}

	return columnToNumOfContainersToUnloadByPortMap;
}
