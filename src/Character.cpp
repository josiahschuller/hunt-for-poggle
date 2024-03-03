/**************************************************
 Project: JosiahSchullerA3
 Author: Josiah Schuller
 Purpose: Character Class Definition File
**************************************************/

#include "Character.h"

// constructor and destructor
Character::Character() {
	name = "Generic name";
	lanternEnergyCells = 15;
	grenades = 5;
	hasKenobi = false;
	gameEnded = false;
	currentCatacomb = 0;	
}
Character::Character(string newName) {
	name = newName;
	lanternEnergyCells = 15;
	grenades = 5;
	hasKenobi = false;
	gameEnded = false;
	currentCatacomb = 0;
}
Character::~Character() {}

// accessors
string Character::getName() {
	return name;
}

int Character::getCatacomb() {
	return currentCatacomb;
}

int Character::getLanternEnergyCells() {
	return lanternEnergyCells;
}

int Character::getGrenades() {
	return grenades;
}

vector<Item*> Character::getItems() {
	return items;
}

bool Character::getHasKenobi() {
	return hasKenobi;
}

bool Character::getGameEnded() {
	return gameEnded;
}

// mutators
void Character::setCatacomb(int catacomb) {
	currentCatacomb = catacomb;
}

void Character::setLanternEnergyCells(int cells) {
	lanternEnergyCells = cells;
}

void Character::setGrenades(int grnds) {
	grenades = grnds;
}

void Character::setHasKenobi(bool kenobi) {
	hasKenobi = kenobi;
}

// other functions
void Character::addItem(Item* item) {
	items.push_back(item);
}

void Character::removeItem(Item* item) {
	for (int index = 0; index < items.size(); index++) {
		if (items[index]->getName() == item->getName()) {
			delete items[index];
			items.erase(items.begin() + index);
			break;
		}
	}
	delete item;
}

string Character::displayInventory() {
	string output = "Anakin's inventory:\n" + to_string(getLanternEnergyCells()) + " lantern energy cells\n" + to_string(getGrenades()) + " grenades\n";
	vector<Item*>::const_iterator whichItem;
	for (whichItem = items.begin(); whichItem != items.end(); whichItem++) {
		Item* thisItem = *whichItem;
		output.append(thisItem->getName() + "\n");
	}
	return output;
}

void Character::gameHasEnded() {
	gameEnded = true;
}