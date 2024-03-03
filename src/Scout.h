/**************************************************
 Project: JosiahSchullerA3
 Author: Josiah Schuller
 Purpose: Scout Geonosian Class Header File
**************************************************/
#ifndef SCOUT_H
#define SCOUT_H
#include "RoamChar.h"
#include <time.h>

class Scout : public RoamChar {
public:
	// constructor and destructor
	Scout();
	~Scout();

	// other functions
	string encounter();
};

#endif