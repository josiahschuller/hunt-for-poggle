/**************************************************
 Project: JosiahSchullerA3
 Author: Josiah Schuller
 Purpose: Item Class Header File
**************************************************/
#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <string>
using namespace std;

class Item {
public:
	// constructor and destructor
	Item();
	Item(string newName);
	~Item();

	// accessors
	string getName();

private:
	// variables
	string name;
};

#endif