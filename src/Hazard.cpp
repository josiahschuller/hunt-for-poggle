/**************************************************
 Project: JosiahSchullerA3
 Author: Josiah Schuller
 Purpose: Hazard Class Definition File
**************************************************/

#include "Hazard.h"

// constructor and destructor
Hazard::Hazard() {
	name = "Generic hazard";
	hint = "Generic hint of generic hazard";
}
Hazard::Hazard(string newName, string newHint) {
	name = newName;
	hint = newHint;
}

Hazard::~Hazard() {}

// accessors
string Hazard::getName() {
	return name;
}

string Hazard::getHint() {
	return hint;
}

int Hazard::getCatacomb() {
	return currentCatacomb;
}

// mutators
void Hazard::setCatacomb(int catacomb) {
	currentCatacomb = catacomb;
}