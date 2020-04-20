#include <iostream>
#include <vector>
#include <map>
#include "ShipPlanColumn.h"

#ifndef SHIP_PLAN_H
#define SHIP_PLAN_H

using std::vector;
using std::string;


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
    ~ShipPlan();
    int getCapacityOfColumn(int xPos, int yPos);
    int getNumOfContainersInColumn(int xPos, int yPos);
    int getShipCapacity();
    void loadContainer(Container* container);
    bool unloadContainer(string& containerId);
    vector<vector<string>> getInstructionsForUnloadAsVector(string& portCode);
    std::map<std::pair<int, int>, int> createColumnToNumOfContainersToUnloadByPortMap(vector<string>& idsOfContainersToUnload);
};

#endif