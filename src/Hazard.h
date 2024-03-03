/**************************************************
 Project: JosiahSchullerA3
 Author: Josiah Schuller
 Purpose: Hazard Class Header File
**************************************************/
#ifndef HAZARD_H
#define HAZARD_H
#include <iostream>
#include <string>
using namespace std;

class Hazard {
public:
	// constructor and destructor
	Hazard();
	Hazard(string newName, string newHint);
	~Hazard();

	// accessors
	string getName();
	string getHint();
	int getCatacomb();

	// mutators
	void setCatacomb(int catacomb);

protected:
	string name;
	string hint;
	int currentCatacomb;
};

#endif