#include <iostream>
#include <vector>
#include <string>
#include "Simulation.h"

Simulation::Simulation(std::string& pathToRootFolder, std::vector<Algorithm*> algorithms): pathToRootFolder_(pathToRootFolder) {
	
	algorithmVector_ = algorithms;
}

Simulation::~Simulation() {}

void Simulation::startSimulation() {



	
}

