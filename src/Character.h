/**************************************************
 Project: JosiahSchullerA3
 Author: Josiah Schuller
 Purpose: Character Class Header File
**************************************************/
#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <string>
#include <vector>
#include "Item.h"
#include "Catacomb.h"
using namespace std;

class Character {
public:
	// constructor and destructor
	Character();
	Character(string newName);
	~Character();

	// accessor methods
	string getName();
	int getCatacomb();
	int getLanternEnergyCells();
	int getGrenades();
	vector<Item*> getItems();
	bool getHasKenobi();
	bool getGameEnded();

	// mutator methods
	void setCatacomb(int catacomb);
	void setLanternEnergyCells(int cells);
	void setGrenades(int grnds);
	void setHasKenobi(bool kenobi);

	// other functions
	void addItem(Item* item);
	void removeItem(Item* item);
	string displayInventory();
	void gameHasEnded();

private:
	// player variables
	string name;
	int currentCatacomb;
	int lanternEnergyCells;
	int grenades;
	vector<Item*> items;
	bool hasKenobi;
	bool gameEnded;
};

#endif