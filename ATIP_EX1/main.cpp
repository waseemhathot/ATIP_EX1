#include <iostream>
#include <vector>
#include <cstdlib>
#include "ship.h"
#include "file_IO.h"
#include <regex>


int main() {


    vector<vector<int>> lines = readShipPlanFromFile("C:/Users/wasse/Desktop/University/Year 7/Semester B/cpp/HW1/files/ship_plan_test.txt");
    printShipPlan(lines);

    vector<string> lines2 = readShipRouteFromFile("C:/Users/wasse/Desktop/University/Year 7/Semester B/cpp/HW1/files/ship_route_test.txt");
    printShipRoute(lines2);

    vector<vector<string>> lines3 = readPortCargoFromFile("C:/Users/wasse/Desktop/University/Year 7/Semester B/cpp/HW1/files/port_cargo_test.txt");
    printPortCargo(lines3);

    return EXIT_SUCCESS;
}



