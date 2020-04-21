#include <iostream>
#include "Algorithm.h"

#ifndef SIMULATION_H
#define SIMULATION_H

class Simulation {

	std::string pathToRootFolder_;
	std::vector<Algorithm*> algorithmVector_;
	std::map<std::string, int> portCodeToNumOfStopsMap_;
	std::vector<std::string> shipRoute_;

public:

	Simulation(std::string& pathToRootFolder, std::vector<Algorithm*>& algorithms);
	~Simulation();

	void startSimulation();
	void initPortCodeToNumOfStopsMap(std::vector<std::string> route);
	void traveShipToPort(Algorithm* algorithm, std::string& travelEntry, std::string& port, int numOfStopsAlreadyMade);
};



#endif