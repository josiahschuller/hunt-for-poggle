/**************************************************
 Project: JosiahSchullerA3
 Author: Josiah Schuller
 Purpose: Roaming character Class Header File
**************************************************/
#ifndef ROAMCHAR_H
#define ROAMCHAR_H
#include <iostream>
#include <string>
using namespace std;

class RoamChar {
public:
	// constructor and destructor
	RoamChar();
	RoamChar(string newType);
	~RoamChar();

	// accessors
	string getType();

	// other functions
	virtual string encounter();

protected:
	string type;
};

#endif