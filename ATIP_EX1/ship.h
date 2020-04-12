#include <iostream>
#include <vector>
#include "container.h"

#ifndef SHIP_H

using std::vector;
using std::string;
using Floor = std::vector<vector<Container>>;
using Route = std::vector<string>;


class ShipPlan {
    vector<Floor> plan_; 

public:
    ShipPlan(vector<Floor> plan);

    int loadContainer(Container& container, int floorIndex, int rowIndex, int colIndex);
    Container& unloadContainer(string containerId, int floorIndex, int rowIndex, int colIndex);
    vector<ContainerPosition> findContainersByDest(string destinationCode);
};

class Ship {
    Route route_;
    ShipPlan shipPlan_; 

public:
    Ship(ShipPlan& shipPlan, Route& route);
};

#endif