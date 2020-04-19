#include <iostream>
#include <vector>
#include <map>
#include "container.h"

#ifndef SHIP_PLAN_H
#define SHIP_PLAN_H

using std::vector;
using std::string;

class ShipPlanColumn {

    vector<Container*> containers_;
    int columnCapacity_;
    int numOfContainersInColumn_;
    int xPos_;
    int yPos_;

public:

    ShipPlanColumn(int columnCapacity, int xPos, int yPos);
    int loadContainer(Container* container);
    void setColumnCapacity(int capacity);
    int getCapacity();
    int getNumOfContainers();
    bool isThereSpaceAvailable();
    std::pair<int, int> getPos();
    vector<vector<string>> getInstructionsToUnloadContainer(string& portCode, int numOfContainersToUnloadForPort);
};

class ShipPlan {

    int numOfFloors_;
    int containersInXDim_;
    int containersInYDim_;
    int shipCapacity_;
    int numOfContainersOnShip_;
    std::map<std::pair<int, int>, ShipPlanColumn*> plan_; //key = position of the map as pair value = pointer to the column.
    std::map<string, ShipPlanColumn*> containersToColumnMap_; // key = container Id, value = pointer to the column it is in.
    std::map<string, vector<string>> portsToContainersIdMap_; //key = column position as pair, value = number of containers in column to be unloaded to the currnt port.

public:

    ShipPlan(vector<vector<int>> shipPlanData);

    int getCapacityOfColumn(int xPos, int yPos);
    int getNumOfContainersInColumn(int xPos, int yPos);
    int getShipCapacity();
    void loadContainer(Container* container);
    void performInstructions(vector<string>& instructions);
    vector<vector<string>> getInstructionsForUnloadAsVector(string& portCode);
    std::map<std::pair<int, int>, int> createColumnToNumOfContainersToUnloadByPortMap(vector<string>& idsOfContainersToUnload);
};


#endif