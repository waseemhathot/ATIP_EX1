#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <filesystem>
#include "Simulation.h"
#include "constants.h"


int main(int argc, char** argv) {

	if (argc != InputFileConstants::numOfExpectedCommandLineArgs) {

		std::cerr << "ERROR: Invalid Num Of Arguments" << std::endl;
		return EXIT_FAILURE;
	}

	std::vector<Algorithm*> algVec;
	Algorithm* alg1 = new Algorithm();
	Algorithm* alg2 = new Algorithm();
	algVec.push_back(alg1);
	algVec.push_back(alg2);

	std::string pathToRootFolder = argv[1];
	Simulation* simulation = new Simulation(pathToRootFolder, algVec);
	simulation->startSimulation();

	delete simulation;

	return EXIT_SUCCESS;
}



