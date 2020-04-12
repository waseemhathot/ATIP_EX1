#include <iostream>
#include <vector>
#include <cstdlib>
#include "container.h"


using std::vector;
using std::string;
using Floor = std::vector<vector<Container>>;
using Route = std::vector<string>;

class ShipPlan {

    vector<Floor> plan_; 

public:
    ShipPlan(vector<Floor> plan): plan_(plan) {}

    int loadContainer(Container& container, int floorIndex, int rowIndex, int colIndex) {

        return EXIT_SUCCESS;
    }


    Container& unloadContainer(string containerId, int floorIndex, int rowIndex, int colIndex) {
        //todo
        Container* unloadedContainer = new Container(5, "ALDRZ", "CSQU3054383"); // just for compiling
        return *unloadedContainer;
    }

    vector<ContainerPosition> findContainersByDest(string destinationCode){
        
    }

};

class Ship {
    Route route_; //containing the destinations in the required order, each index contains a seaport code.
    ShipPlan shipPlan_; 

public:
    Ship(ShipPlan& shipPlan, Route& route): shipPlan_(shipPlan), route_(route)  {}

};