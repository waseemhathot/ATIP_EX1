#include <iostream>
#include <cstdlib>
#include "ShipPlan.h"



ShipPlan::ShipPlan(std::vector<std::vector<int>> shipPlanData) : numOfContainersOnShip_(0) {

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

ShipPlan::~ShipPlan() {

	std::map<std::pair<int, int>, ShipPlanColumn*>::iterator it = plan_.begin();
	while (it != plan_.end()) {
		delete it->second;
		it++;
	}
	containersToColumnMap_.clear();
	plan_.clear();
	portsToContainersIdMap_.clear();
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


std::vector<int> ShipPlan::findSpaceToLoad() {

	bool isSpaceFound = false;
	std::vector<int> location;
	std::map<std::pair<int, int>, ShipPlanColumn*>::iterator it = plan_.begin();
	while (!isSpaceFound && it != plan_.end()) {

		ShipPlanColumn* column = it->second;
		if (column->isThereSpaceAvailable()) {
			
			isSpaceFound = true;
			int xPos = column->getXPos();
			int yPos = column->getYPos();
			int floor = column->getNumOfContainers();
			location = { floor, xPos, yPos };
		}
	}

	return location;
}

void ShipPlan::loadContainer(Container* container, int floor, int xPos, int yPos) {

	std::pair<int, int> pos = std::make_pair(xPos, yPos);
	ShipPlanColumn* selectedColumn = plan_[pos];
	selectedColumn->loadContainer(container);
	containersToColumnMap_[container->getContainerId()] = selectedColumn;
	numOfContainersOnShip_ += 1;
}

Container* ShipPlan::unloadContainer(int xPos, int yPos) {

	ShipPlanColumn* columnOfTheContainer = plan_[std::make_pair(xPos, yPos)];
	Container* unloadedContainer = columnOfTheContainer->unloadTopContainer();

	containersToColumnMap_.erase(unloadedContainer->getContainerId());
	numOfContainersOnShip_ -= 1;

	return unloadedContainer;
}

std::vector<std::vector<std::string>> ShipPlan::getInstructionsForUnloadAtPort(std::string& portCode) {

	std::vector<std::string> idsOfContainersToBeUnloaded = portsToContainersIdMap_[portCode];
	std::vector<std::vector<std::string>> instructions;

	std::map<std::pair<int, int>, int> colToNumOfContainersMap = createColumnToNumOfContainersToUnloadByPortMap(idsOfContainersToBeUnloaded);
	std::map<std::pair<int, int>, int>::iterator it = colToNumOfContainersMap.begin();

	while (it != colToNumOfContainersMap.end()) {

		ShipPlanColumn* currColumn = plan_[it->first];
		int numOfContainersToUnload = it->second;

		std::vector<std::vector<std::string>> instrForCurrColumn = currColumn->getInstructionsToUnloadContainers(portCode, numOfContainersToUnload);
		instructions.insert(instructions.end(), instrForCurrColumn.begin(), instrForCurrColumn.end());

		it++;
	}

	colToNumOfContainersMap.clear();
	return instructions;
}


std::map<std::pair<int, int>, int> ShipPlan::createColumnToNumOfContainersToUnloadByPortMap(std::vector<std::string>& idsOfContainersToUnload) {

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

