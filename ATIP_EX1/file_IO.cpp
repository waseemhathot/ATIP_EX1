#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include "constants.h"

using std::vector;
using std::string;
using std::stringstream;

////////////////////////////////////////////// READ FROM FILE /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool isLineFormatValid(std::string line, std::regex reg) {

	if (!(std::regex_match(line, reg))) {
		return false;
	}

	return true;
}

vector<string> getTokensFromLineIntoVector(string& line) { //takes tokens separated with whitespaces

	vector<string> lineTokensVector;
	std::smatch stringMatch;
	std::regex tokensInlineRegex(InputFileConstants::getTokensInLineRegexstring);

	string currentString = line;
	while (std::regex_search(currentString, stringMatch, tokensInlineRegex)) {

		lineTokensVector.push_back(stringMatch[0]);
		currentString = stringMatch.suffix();
	}

	return lineTokensVector;
}

vector<vector<string>> readFileByLineIntoVector(const std::string& filename, std::regex reg) {

	string line;
	std::ifstream fin(filename);
	vector<vector<string>> result;

	if (fin.is_open()) {

		while (std::getline(fin, line)) {

			vector<string> tokensInLine;
			if (isLineFormatValid(line, reg)) {

				tokensInLine = getTokensFromLineIntoVector(line);
				result.push_back(tokensInLine);
			}
			else {
				std::cout << "WARNING! Bad input: " << line << std::endl;
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
	const std::regex shipPlanRegex(InputFileConstants::shipPlanRegexString);

	vector<vector<string>> fileLinesInVector = readFileByLineIntoVector(filename, shipPlanRegex);

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
	const std::regex shipRouteRegex(InputFileConstants::shipRouteRegexString);

	vector<vector<string>> fileLinesInVector = readFileByLineIntoVector(filename,  shipRouteRegex);

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
	const std::regex portCargoRegex(InputFileConstants::portCargoRegexString);

	vector<vector<string>> fileLinesInVector = readFileByLineIntoVector(filename, portCargoRegex);

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
