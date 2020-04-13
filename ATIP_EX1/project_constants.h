#include <iostream>
#include <regex>
#include <string>

#ifndef PROJECT_CONSTANTS_H
#define PROJECT_CONSTANTS_H


namespace InputFileConstants {

	const size_t numOfArgsInShipPlanLine = 3;
	const size_t numOfArgsInShipRouteLine = 1;
	const size_t numOfArgsInPortCargoLine = 3;
	const std::string shipPlanRegexString = "\\s*[1-9]+\\s*,\\s*[1-9]+\\s*,\\s*[1-9]+\\s*";
	const std::string shipRouteRegexString = "\\s*[A-Z]{5}\\s*";
	const std::string portCargoRegexString = "\\s*([A-Z]{3}[UJZ]{1}[0-9]{7})\\s*,\\s*[0-9]+\\s*,\\s*[A-Z]{5}\\s*";
	const std::string getTokensInLineRegexstring = "[^\\s,]+";
}

#endif