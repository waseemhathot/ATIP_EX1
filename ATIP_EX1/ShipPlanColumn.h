#include <iostream>
#include "container.h"

#ifndef SHIP_PLAN_COLUMN_H
#define SHIP_PLAN_COLUMN_H

class ShipPlanColumn {

	std::vector<Container*> containers_;
	int columnCapacity_;
	int numOfContainersInColumn_;
	int xPos_;
	int yPos_;

public:

	ShipPlanColumn(int columnCapacity, int xPos, int yPos);
	~ShipPlanColumn();
	bool loadContainer(Container* container);
	Container* unloadTopContainer();
	void setColumnCapacity(int capacity);
	int getCapacity();
	int getNumOfContainers();
	bool isThereSpaceAvailable();
	std::pair<int, int> getPos();
	int getXPos();
	int getYPos();
	std::vector<std::vector<std::string>> getInstructionsToUnloadContainersForPort(std::string& portCode, int numOfContainersToUnloadForPort);
	std::vector<std::vector<std::string>> getInstructionsToUnloadAllContainers();
};


#endif