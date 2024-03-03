/**************************************************
 Project: JosiahSchullerA3
 Author: Josiah Schuller
 Purpose: Thief Geonosian Class Definition File
**************************************************/

#include "Thief.h"

// constructor and destructor
Thief::Thief() : RoamChar("Thief Geonosian") {}

Thief::~Thief() {}

string Thief::encounter() {
	// what does the thief steal?
	srand(time(NULL));
	int outcome = rand() % 2 == 0;
	if (outcome <= 1) {
		return "Lantern energy cell";
	}
	else if (outcome == 2) {
		return "Grenade";
	}
	else {
		return "Nothing";
	}
}