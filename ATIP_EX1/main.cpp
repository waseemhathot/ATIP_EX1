#include <iostream>
#include <vector>
#include <cstdlib>
#include "file_IO.h"
#include "Simulation.h"
#include <fstream>

using std::vector;

int main() {


   /*vector<vector<int>> lines = readShipPlanFromFile("C:/Users/wasse/Desktop/University/Year 7/Semester B/cpp/HW1/ship_plan_test.txt");*/
    
    Algorithm* testAlg = new Algorithm();
    testAlg->readShipPlan("C:/Users/wasse/Desktop/University/Year 7/Semester B/cpp/HW1/ship_plan_test.txt");
    testAlg->readShipRoute("C:/Users/wasse/Desktop/University/Year 7/Semester B/cpp/HW1/ship_route_test.txt");
    testAlg->getInstructionsForCargo("C:/Users/wasse/Desktop/University/Year 7/Semester B/cpp/HW1/ALDRZ_1.txt", "C:/Users/wasse/Desktop/University/Year 7/Semester B/cpp/HW1/instructionOutput.txt");
    testAlg->getInstructionsForCargo("C:/Users/wasse/Desktop/University/Year 7/Semester B/cpp/HW1/DZDEL_1.txt", "C:/Users/wasse/Desktop/University/Year 7/Semester B/cpp/HW1/instructionOutput.txt");
   
    delete testAlg;
    return EXIT_SUCCESS;
}



