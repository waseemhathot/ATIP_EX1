#include <iostream>
#include <regex>
#include <string>

#ifndef PROJECT_CONSTANTS_H
#define PROJECT_CONSTANTS_H


namespace InputFileConstants {

	const size_t numOfArgsInShipPlanLine = 3;
	const size_t numOfArgsInShipRouteLine = 1;
	const size_t numOfArgsInPortCargoLine = 3;
	const char shipPlanDelimiter = ',';
	const char shipRouteDelimiter = 'q'; //whitespace
	const char portCargoDelimiter = ' ';
}

#endif