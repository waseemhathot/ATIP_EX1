#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#ifndef FILE_IO_H
#define FILE_IO_H

using std::vector;
using std::string;

using InputShipPlan = std::tuple<int, int , int>;


vector<vector<int>> readShipPlanFromFile(const std::string& filename);

vector<string> readShipRouteFromFile(const std::string& filename);

vector<vector<string>> readPortCargoFromFile(const std::string& filename);

void printShipPlan(vector<vector<int>> shipPlanInVector);

void printShipRoute(vector<string> shipRouteVec);

void printPortCargo(vector<vector<string>> lines);

#endif