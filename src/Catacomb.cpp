/**************************************************
 Project: JosiahSchullerA3
 Author: Josiah Schuller
 Purpose: Catacomb Class Definition File
**************************************************/

#include "Catacomb.h"

// constructor and destructor
Catacomb::Catacomb() {
	catName = "Generic catacomb";
	catDescription = "Generic description of a generic catacomb";
	catExits = "";
	northCatacomb = -1;
	eastCatacomb = -1;
	southCatacomb = -1;
	westCatacomb = -1;
	catItem = nullptr;
	catHazard = nullptr;
	catRoamChar = nullptr;
}

Catacomb::Catacomb(string name, string description, string exits, int northIndex, int eastIndex, int southIndex, int westIndex) {
	catName = name;
	catDescription = description;
	catExits = exits;

	// The following refer to the indices of catacombs in the catacombList in the application file.
	// A value of -1 indicates that you cannot travel in that direction.
	northCatacomb = northIndex;
	eastCatacomb = eastIndex;
	southCatacomb = southIndex;
	westCatacomb = westIndex;
	catItem = nullptr;
	catHazard = nullptr;
	catRoamChar = nullptr;
}
Catacomb::~Catacomb() {}

// accessors
string Catacomb::getName() {
	return catName;
}

string Catacomb::getDescription() {
	return catDescription;
}

string Catacomb::getExits() {
	return catExits;
}

Item* Catacomb::getItem() {
	return catItem;
}

Hazard* Catacomb::getHazard() {
	return catHazard;
}

RoamChar* Catacomb::getRoamChar() {
	return catRoamChar;
}

int Catacomb::getNorthCatacomb() {
	return northCatacomb;
}

int Catacomb::getEastCatacomb() {
	return eastCatacomb;
}

int Catacomb::getSouthCatacomb() {
	return southCatacomb;
}

int Catacomb::getWestCatacomb() {
	return westCatacomb;
}

// mutators
void Catacomb::setItem(Item* item) {
	catItem = item;
}

void Catacomb::setHazard(Hazard* hazard) {
	catHazard = hazard;
}

void Catacomb::setRoamChar(RoamChar* roamChar) {
	catRoamChar = roamChar;
}

// other functions
string Catacomb::getCatacombDetails() {
	string output = getName() + "\nDescription: " + getDescription() + "\nExits: " + getExits() + "\n";
	if (getItem() != NULL) {
		output.append("\nItem: " + getItem()->getName() + "\n");
	}
	if (getHazard() != NULL) {
		output.append("\nHAZARD: " + getHazard()->getName() + "\n");
	}
	if (getRoamChar() != NULL) {
		output.append("\nRoaming character: " + getRoamChar()->getType() + "\n");
	}	
	return output;
}