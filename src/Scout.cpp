/**************************************************
 Project: JosiahSchullerA3
 Author: Josiah Schuller
 Purpose: Scout Geonosian Class Definition File
**************************************************/

#include "Scout.h"

// constructor and destructor
Scout::Scout() : RoamChar("Scout Geonosian") {}

Scout::~Scout() {}

string Scout::encounter() {
	// does the scout escape the character?
	srand(time(NULL));
	if (rand() % 2 == 0) {
		return "true";
	}
	else {
		return "false";
	}
}