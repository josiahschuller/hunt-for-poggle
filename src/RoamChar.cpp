/**************************************************
 Project: JosiahSchullerA3
 Author: Josiah Schuller
 Purpose: Roaming character Class Definition File
**************************************************/

#include "RoamChar.h"

// constructor and destructor
RoamChar::RoamChar() {
	type = "Generic type";
}
RoamChar::RoamChar(string newType) {
	type = newType;
}

RoamChar::~RoamChar() {}

// accessors
string RoamChar::getType() {
	return type;
}

string RoamChar::encounter() {
	return "default";
}