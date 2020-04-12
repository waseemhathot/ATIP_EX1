#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include "project_constants.h"

using std::vector;
using std::string;
using std::stringstream;

////////////////////////////////////////////// READ FROM FILE /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool checkLineFormat(std::string line, std::regex reg) {

	if (!(std::regex_match(line, reg))) {
		std::cout << "WARNING! Bad input: " << line << std::endl;
		return false;
	}

	return true;
}

vector<vector<string>> readFileByLineIntoVector(const std::string& filename, const char delimiter, std::regex reg) {

	string line;
	std::ifstream fin(filename);
	vector<vector<string>> result;

	if (fin.is_open()) {

		while (std::getline(fin, line)) {

			vector<string> tokensInLine;
			if (checkLineFormat(line, reg)) {

				stringstream ss(line);
				string token;

				while (std::getline(ss, token, delimiter)) {

					token.erase(std::remove_if(token.begin(), token.end(), isspace), token.end()); //removes white spaces, incase of leading white space
					tokensInLine.push_back(token);
				}

				result.push_back(tokensInLine);
			}
		}



		fin.close();
		return result;
	}
	else std::cout << "Unable to open file";
	 
	return result;
}


///////////////////////////////////////////////////////////
/////////////////////////////// SHIP PLAN FROM FILE /////////////////////////////
//////////////////////////////////////////////////////////////////////////


vector<vector<int>> readShipPlanFromFile(const std::string& filename) {

	vector<vector<int>> shipPlan;
	const std::regex shipPlanRegex("\\s*[1-9]+\\s*,\\s*[1-9]+\\s*,\\s*[1-9]+\\s*");
	vector<vector<string>> fileLinesInVector = readFileByLineIntoVector(filename, InputFileConstants::shipPlanDelimiter, shipPlanRegex);

	if (!fileLinesInVector.empty()) {

		int numFloors = stoi(fileLinesInVector.at(0).at(0));
		int numContainersInX = stoi(fileLinesInVector.at(0).at(1));
		int numContainersInY = stoi(fileLinesInVector.at(0).at(2));

		vector<int> firstLine = { numFloors, numContainersInX, numContainersInY };
		shipPlan.push_back(firstLine);

		vector<int> planLine;
		for (size_t i = 1; i < fileLinesInVector.size(); ++i) {

			int posX = stoi(fileLinesInVector.at(i).at(0));
			int posY = stoi(fileLinesInVector.at(i).at(1));
			int actualNumOfFloors = stoi(fileLinesInVector.at(i).at(2));

			if (posX <= numContainersInX && posX >= 0 && posY <= numContainersInY && posY >= 0 && actualNumOfFloors < numFloors
				&& actualNumOfFloors >= 0) {

				planLine = { posX, posY, actualNumOfFloors };
				shipPlan.push_back(planLine);
			}
		}
	}

	return shipPlan;
}

//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// ROUTE FROM FILE /////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

vector<string> readShipRouteFromFile(const std::string& filename) {


	vector<string> shipRoute;
	const std::regex shipRouteRegex("\\s*[A-Z]{5}\\s*");

	vector<vector<string>> fileLinesInVector = readFileByLineIntoVector(filename, InputFileConstants::shipRouteDelimiter, shipRouteRegex);

	for (size_t i = 0; i < fileLinesInVector.size(); ++i) {

		shipRoute.push_back(fileLinesInVector.at(i).at(0));
	}

	return shipRoute;
}

//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// CARGO FROM FILE /////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


vector<vector<string>> readPortCargoFromFile(const std::string& filename) {

	vector<vector<string>> portCargo;
	const std::regex portCargoRegex("\\s*([A-Z]{3}[UJZ]{1}[0-9]{7})\\s*[0-9]+\\s*[A-Z]{5}\\s*");
	vector<vector<string>> fileLinesInVector = readFileByLineIntoVector(filename, InputFileConstants::portCargoDelimiter, portCargoRegex);

	return fileLinesInVector;
}


//FOR TESTING
void printShipPlan(vector<vector<int>> shipPlanInVector) {

	for (size_t i = 0; i < shipPlanInVector.size(); ++i) {
		std::cout << shipPlanInVector.at(i).at(0) << " " << shipPlanInVector.at(i).at(1) << " " << shipPlanInVector.at(i).at(2) << " " << std::endl;
	}
}

void printShipRoute(vector<string> shipRouteVec) {
	for (size_t i = 0; i < shipRouteVec.size(); ++i) {
		std::cout << shipRouteVec.at(i) << std::endl;
	}
}

void printPortCargo(vector<vector<string>> portCargoInVector) {

	for (size_t i = 0; i < portCargoInVector.size(); ++i) {
		std::cout << portCargoInVector.at(i).at(0) << " " << portCargoInVector.at(i).at(1) << " " << portCargoInVector.at(i).at(2) << std::endl;
	}
}
