/**************************************************
 Project: JosiahSchullerA3
 Author: Josiah Schuller
 Purpose: Thief Geonosian Class Header File
**************************************************/
#ifndef THIEF_H
#define THIEF_H
#include "RoamChar.h"
#include <time.h>

class Thief : public RoamChar {
public:
	// constructor and destructor
	Thief();
	~Thief();

	// other functions
	string encounter();
};

#endif