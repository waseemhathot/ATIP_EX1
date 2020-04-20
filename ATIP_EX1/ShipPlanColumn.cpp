#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <string>
#include "ShipPlanColumn.h"

using std::vector;
using std::string;

ShipPlanColumn::ShipPlanColumn(int columnCapacity, int xPos, int yPos) :
	columnCapacity_(columnCapacity),
	numOfContainersInColumn_(0),
	yPos_(yPos),
	xPos_(xPos)
{}

ShipPlanColumn::~ShipPlanColumn() {
	std::vector<Container*>::iterator it = containers_.begin();
	while (it != containers_.end()) {

		delete *it;
		it++;
	}

	containers_.clear();
}

bool ShipPlanColumn::loadContainer(Container* container) {

	if (containers_.size() == columnCapacity_) {

		return false;
	}
	containers_.push_back(container);
	numOfContainersInColumn_ += 1;

	return true;
}

Container* ShipPlanColumn::unloadTopContainer() {

	Container* topContainer = containers_.at(numOfContainersInColumn_ - 1);
	containers_.pop_back();

	return topContainer;
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

int ShipPlanColumn::getXPos() {
	
	return xPos_;
}
int ShipPlanColumn::getYPos() {

	return yPos_;
}

vector<vector<string>> ShipPlanColumn::getInstructionsToUnloadContainers(string& portCode, int numOfContainersToUnloadForPort) {

	vector<vector<string>> instructions;
	vector<string> currInstruction;
	int containersToUnloadFound = 0;

	for (size_t i = containers_.size() - 1; i >= 0 && containersToUnloadFound < numOfContainersToUnloadForPort; i--) {

		string currContainerId = containers_.at(i)->getContainerId();
		string currContainerPortCode = containers_.at(i)->getDestCode();

		currInstruction = { currContainerId, std::to_string(i), std::to_string(xPos_), std::to_string(yPos_) };
		instructions.push_back(currInstruction);

		if (portCode == currContainerPortCode) {

			containersToUnloadFound += 1;
		}
	}

	return instructions;
}
