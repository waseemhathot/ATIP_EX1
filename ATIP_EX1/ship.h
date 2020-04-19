#include <iostream>
#include <vector>
#include <map>
#include "ShipPlan.h"

#ifndef SHIP_H
#define SHIP_H

using std::vector;
using std::string;
using Route = std::vector<string>;

class Ship {
    Route route_;
    ShipPlan shipPlan_; 

public:
    Ship(ShipPlan& shipPlan, Route& route);
};

#endif