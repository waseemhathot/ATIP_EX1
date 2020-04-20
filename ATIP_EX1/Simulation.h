#include <iostream>
#include <vector>
#include <string>
#include "Algorithm.h"

#ifndef SIMULATION_H
#define SIMULATION_H

class Simulation {

	std::string pathToRootFolder_;
	std::vector<Algorithm*> algorithmVector_;

public:

	Simulation(std::string& pathToRootFolder, std::vector<Algorithm*> algorithms);
	~Simulation();

	void startSimulation();
};



#endif