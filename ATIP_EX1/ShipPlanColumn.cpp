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

bool ShipPlanColumn::unloadTopContainer(string& containerId) {


	string topContainerId = containers_.at(numOfContainersInColumn_ - 1)->getContainerId();

	if (numOfContainersInColumn_ == 0 || containerId != topContainerId) {

		std::cout << "ERROR: container not on top or no container on that position" << std::endl;
		return false;
	}

	containers_.pop_back();
	return true;
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

vector<vector<string>> ShipPlanColumn::getInstructionsToUnloadContainer(string& portCode, int numOfContainersToUnloadForPort) {

	vector<vector<string>> instructions;
	vector<vector<string>> loadBackInstructions;
	vector<string> currInstruction;
	int containersToUnloadFound = 0;

	for (size_t i = containers_.size() - 1; i >= 0 && containersToUnloadFound < numOfContainersToUnloadForPort; i--) {

		string currContainerId = containers_.at(i)->getContainerId();
		string currContainerPortCode = containers_.at(i)->getDestCode();

		currInstruction = { "U", currContainerId, std::to_string(i), std::to_string(xPos_), std::to_string(yPos_) };
		instructions.push_back(currInstruction);

		if (portCode == currContainerPortCode) {

			containersToUnloadFound += 1;
		}
		else {


			currInstruction = { "L", currContainerId, std::to_string(i), std::to_string(xPos_), std::to_string(yPos_) };
			loadBackInstructions.push_back(currInstruction);
		}
	}

	instructions.insert(instructions.end(), loadBackInstructions.begin(), loadBackInstructions.end());

	return instructions;
}
