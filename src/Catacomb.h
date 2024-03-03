/**************************************************
 Project: JosiahSchullerA3
 Author: Josiah Schuller
 Purpose: Catacomb Class Header File
**************************************************/
#ifndef CATACOMB_H
#define CATACOMB_H
#include <iostream>
#include <string>
#include "Item.h"
#include "Hazard.h"
#include "RoamChar.h"
using namespace std;

class Catacomb {
public:
	// constructor and destructor
	Catacomb();
	Catacomb(string name, string description, string exits, int northIndex, int eastIndex, int southIndex, int westIndex);
	~Catacomb();

	// accessors
	string getName();
	string getDescription();
	string getExits();
	Item* getItem();
	Hazard* getHazard();
	RoamChar* getRoamChar();
	int getNorthCatacomb();
	int getEastCatacomb();
	int getSouthCatacomb();
	int getWestCatacomb();

	// mutators
	void setItem(Item* item);
	void setHazard(Hazard* hazard);
	void setRoamChar(RoamChar* roamChar);

	// other functions
	string getCatacombDetails();

private:
	// variables
	string catName;
	string catDescription;
	string catExits;
	Item* catItem;
	Hazard* catHazard;
	RoamChar* catRoamChar;
	int northCatacomb;
	int eastCatacomb;
	int southCatacomb;
	int westCatacomb;
};

#endif