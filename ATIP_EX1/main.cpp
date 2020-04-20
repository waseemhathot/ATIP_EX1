#include <iostream>
#include <vector>
#include <cstdlib>
#include "file_IO.h"
#include "ShipPlan.h"
#include <fstream>

using std::vector;

int main() {


   /* vector<vector<int>> lines = readShipPlanFromFile("C:/Users/wasse/Desktop/University/Year 7/Semester B/cpp/HW1/ship_plan_test.txt");
    printShipPlan(lines);

    ShipPlan* plan = new ShipPlan(lines);
    int res = plan->getCapacityOfColumn(0, 0);
    int res2 = plan->getShipCapacity();

    string portCode = "ALDRZ";
    string containerId = "CSQU3054383";
    Container* container = new Container(5, portCode, containerId);
    plan->loadContainer(container);
    Container* container2 = new Container(5, "ISDRZ", "CGU3054383");
    plan->loadContainer(container2);

    vector<vector<string>> instructions = plan->getInstructionsForUnloadAsVector(portCode);

    std::cout << plan->getNumOfContainersInColumn(0, 0) << std::endl;
    std::cout << instructions.size() << std::endl;
    std::cout << instructions.at(0).at(0) << std::endl;
    std::cout << instructions.at(0).at(1) << std::endl;
    std::cout << instructions.at(0).at(2) << std::endl;

    delete plan;*/


    //vector<string> lines2 = readShipRouteFromFile("path to file");
    //printShipRoute(lines2);



    //vector<vector<string>> lines3 = readPortCargoFromFile("path to file");
    //printPortCargo(lines3);

    return EXIT_SUCCESS;
}



