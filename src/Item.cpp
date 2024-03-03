/**************************************************
 Project: JosiahSchullerA3
 Author: Josiah Schuller
 Purpose: Item Class Definition File
**************************************************/

#include "Item.h"

// constructor and destructor
Item::Item() {
	name = "Generic item";
}
Item::Item(string newName) {
	name = newName;
}
Item::~Item() {}

// accessors
string Item::getName() {
	return name;
}
