#include <iostream>
#include <map>
#include "ShipPlanColumn.h"

#ifndef SHIP_PLAN_H
#define SHIP_PLAN_H

class ShipPlan {

    int numOfFloors_;
    int containersInXDim_;
    int containersInYDim_;
    int shipCapacity_;
    int numOfContainersOnShip_;
    std::map<std::pair<int, int>, ShipPlanColumn*> plan_; //key = position of the map as pair value = pointer to the column.
    std::map<std::string, ShipPlanColumn*> containersToColumnMap_; // key = container Id, value = pointer to the column it is in.
    std::map<std::string, std::vector<std::string>> portsToContainersIdMap_; //key = column position as pair, value = number of containers in column to be unloaded to the currnt port.

public:

    ShipPlan(std::vector<std::vector<int>> shipPlanData);
    ~ShipPlan();
    int getCapacityOfColumn(int xPos, int yPos);
    int getNumOfContainersInColumn(int xPos, int yPos);
    int getShipCapacity();
    std::vector<int> findSpaceToLoad();
    void loadContainer(Container* container, int floor, int xPos, int yPos);
    Container* unloadContainer(int xPos, int yPos);
    std::vector<std::vector<std::string>> getInstructionsForUnloadAtPort(std::string& portCode);
    std::map<std::pair<int, int>, int> createColumnToNumOfContainersToUnloadByPortMap(std::vector<std::string>& idsOfContainersToUnload);
};

#endif