#include <iostream>
#include "Algorithm.h"

#ifndef SIMULATION_H
#define SIMULATION_H

class Simulation {

	std::string pathToRootFolder_;
	std::vector<Algorithm*> algorithmVector_;
	//std::map<std::string, int> portCodeToNumOfStopsMap_;
	//std::vector<std::string> shipRoute_;

public:

	Simulation(std::string& pathToRootFolder, std::vector<Algorithm*>& algorithms);
	~Simulation();

	void startSimulation();

private:
	void initAlgorithms(std::filesystem::directory_entry travelEntr);
	std::map<std::string, int> getPortCodeToNumOfStopsMap(std::vector<std::string> route);
	void traveShipToPort(Algorithm* algorithm, std::string& travelEntry, std::string& port, int numOfStopsAlreadyMade);
	void writeLineToFile(std::string& line, std::string& path);
	void writeResultsLine(std::string& line);
	void clearFile(std::string& path);
	void clearResultsFile();
	void clearErrorsFile();
};




#endif