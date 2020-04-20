#include <iostream>
#include <vector>
#include <map>
#include "container.h"

#ifndef SHIP_PLAN_COLUMN_H
#define SHIP_PLAN_COLUMN_H

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
    ~ShipPlanColumn();
    bool loadContainer(Container* container);
    bool unloadTopContainer(string& containerId);
    void setColumnCapacity(int capacity);
    int getCapacity();
    int getNumOfContainers();
    bool isThereSpaceAvailable();
    std::pair<int, int> getPos();
    vector<vector<string>> getInstructionsToUnloadContainer(string& portCode, int numOfContainersToUnloadForPort);
};


#endif