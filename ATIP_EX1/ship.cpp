#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include "ship.h"

using std::vector;
using std::string;
using Route = std::vector<string>;

Ship::Ship(ShipPlan& shipPlan, Route& route) : shipPlan_(shipPlan), route_(route) {}

