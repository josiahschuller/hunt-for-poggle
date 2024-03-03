/**************************************************
 Project: JosiahSchullerA3
 Author: Josiah Schuller
 Purpose: Application file for the actual game
**************************************************/

#include "Application.h"

int main() {
	srand(unsigned(time(NULL)));

	// Display title and rules
	displayTitle();
	displayRules();

	// Setup game
	setupGame();

	// Play game
	playGame();

	// Memory management
	cleanMemory();

	// Wait then exit
	system("pause");
	return 0;
}

void displayTitle() {
	// This function displays the game title
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "          The Search for Poggle the Lesser\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

void displayRules() {
	// This function loads the game rules from a txt file and displays them.
	ifstream fileToRead("rules.txt");

	if (fileToRead.is_open()) {
		string line = "";
		while (!fileToRead.eof()) {
			getline(fileToRead, line);
			if (line != "") {
				cout << line << "\n";
			}
		}
	}
	fileToRead.close();
	askForString("Press any key to start playing: ");
}

void setupGame() {
	system("CLS");
	displayTitle();

	// setup catacombs
	setupCatacombs();


	// setup difficulty level
	bool validInput = false;
	string userInput = askForString("Which difficulty would you like to play at?\n -Padawan (p): an easier experience\n -Jedi knight (k): the standard playthrough\n -Jedi master (m): if you seek true mastery...\n");
	while (validInput == false) {
		char userInputChar = tolower(userInput[0]);
		switch (userInputChar) {
		case 'p':
			// padawan difficulty
			assignHazard(new Poggle());
			assignHazard(new Nest());
			assignItem(new Item("Lantern battery"));
			assignItem(new Item("Lantern battery"));
			assignItem(new Item("Lantern battery"));
			assignItem(new Item("Extra grenade"));
			assignItem(new Item("Extra grenade"));
			assignItem(new Item("Extra grenade"));
			assignItem(new Item("Silent boots"));
			assignRoamChar(new ObiWanKenobi());
			validInput = true;
			break;
		case 'k':
			// jedi knight difficulty
			assignHazard(new Poggle());
			assignHazard(new HiveQueen());
			assignHazard(new Nest());
			assignHazard(new Nest());
			assignItem(new Item("Lantern battery"));
			assignItem(new Item("Lantern battery"));
			assignItem(new Item("Extra grenade"));
			assignItem(new Item("Extra grenade"));
			assignItem(new Item("Ultraviolet flashlight"));
			assignItem(new Item("Ultraviolet flashlight"));
			assignItem(new Item("Silent boots"));
			assignRoamChar(new Scout());
			assignRoamChar(new Thief());
			assignRoamChar(new ObiWanKenobi());
			validInput = true;
			break;
		case 'm':
			// jedi master difficulty
			assignHazard(new Poggle());
			assignHazard(new HiveQueen());
			assignHazard(new Nest());
			assignHazard(new Nest());
			assignItem(new Item("Lantern battery"));
			assignItem(new Item("Extra grenade"));
			assignItem(new Item("Ultraviolet flashlight"));
			assignItem(new Item("Silent boots"));
			assignRoamChar(new Scout());
			assignRoamChar(new Scout());
			assignRoamChar(new Thief());
			assignRoamChar(new Thief());
			validInput = true;
			break;
		default:
			userInput = askForString("\nType 'p' for padawan, 'k' for jedi knight, or 'm' for jedi master: ");
		}
	}


	// setup player character
	string name = askForString("What is the name of your character? ");
	character = new Character(name);
}

void setupCatacombs() {
	// retrieve catacomb details from catacombs.txt add catacombs to the catacombs vector
	ifstream fileToRead("catacombs.txt");
	if (fileToRead.is_open()) {
		string line = "";
		while (!fileToRead.eof()) {
			getline(fileToRead, line);
			if (line != "") {
				string name = line.substr(0, line.find(","));
				line.erase(0, line.find(",") + 1);
				string description = line.substr(0, line.find(","));
				line.erase(0, line.find(",") + 1);
				string exits = line.substr(0, line.find(","));
				line.erase(0, line.find(",") + 1);
				int northIndex = stoi(line.substr(0, line.find(",")));
				line.erase(0, line.find(",") + 1);
				int eastIndex = stoi(line.substr(0, line.find(",")));
				line.erase(0, line.find(",") + 1);
				int southIndex = stoi(line.substr(0, line.find(",")));
				line.erase(0, line.find(",") + 1);
				int westIndex = stoi(line);
				line.erase(0, line.find(",") + 1);
				catacombList.push_back(new Catacomb(name, description, exits, northIndex, eastIndex, southIndex, westIndex));
			}
		}
	}
}

void assignHazard(Hazard* hazard) {
	// This function is used to assign hazards to their starting positions.
	bool ok = false;
	int catacombIndex;
	Catacomb* catacomb = catacombList[0];
	// Check if the catacomb already has a hazard. If it does, select another catacomb.
	while (ok == false) {
		catacombIndex = 1 + rand() % (catacombList.size() - 1);
		catacomb = catacombList[catacombIndex];
		if (catacomb->getHazard() == nullptr) {
			ok = true;
		}
	}
	// Set the hazard's location
	hazard->setCatacomb(catacombIndex);
	catacomb->setHazard(hazard);
	if (testingMode) {
		cout << "TESTING MODE: " << hazard->getName() << " has been assigned to " << catacomb->getName() << endl;
	}
}

void assignItem(Item* item) {
	// This function is used to assign items to their starting positions.
	bool ok = false;
	Catacomb* catacomb = catacombList[0];
	// Check if the catacomb already has an item. If it does, select another catacomb.
	while (ok == false) {
		catacomb = catacombList[rand() % catacombList.size()];
		if (catacomb->getItem() == nullptr) {
			ok = true;
		}
	}
	catacomb->setItem(item);
	if (testingMode) {
		cout << "TESTING MODE: " << item->getName() << " has been assigned to " << catacomb->getName() << endl;
	}
}

void assignRoamChar(RoamChar* roamChar) {
	// This function is used to assign roaming characters to their starting positions.
	bool ok = false;
	Catacomb* catacomb = catacombList[0];
	// Check if the catacomb already has a roaming character. If it does, select another catacomb.
	while (ok == false) {
		catacomb = catacombList[1 + rand() % (catacombList.size() - 1)];
		if (catacomb->getRoamChar() == nullptr) {
			ok = true;
		}
	}
	catacomb->setRoamChar(roamChar);
	if (testingMode) {
		cout << "TESTING MODE: " << roamChar->getType() << " has been assigned to " << catacomb->getName() << endl;
	}
}

void playGame() {
	// While the character is still alive
	while (not character->getGameEnded()) {
		// Let the user have their turn
		userTurn(character);

		// Check if the character has ran out of lantern energy cells
		if (character->getLanternEnergyCells() <= 0) {
			character->gameHasEnded();
			cout << character->getName() << " has run out of lantern energy cells!\nGame over!\n";
		}

		// Check if there are no grenades left in the game
		if (not checkGrenades) {
			character->gameHasEnded();
			cout << "There are no more grenades left!\nGame over!\n";
		}

		// Move the roaming characters
		if (not character->getGameEnded()) {
			moveRoamChars();
		}
	}
}

void userTurn(Character* character) {
	// display UI
	while (displayUI(character) == false) {
		displayUI(character);
	}

	Catacomb* currentCatacomb = catacombList[character->getCatacomb()];

	if (character->getGameEnded() == false) {
		// ask user what they want to do
		bool validInput = false;
		string userInput;
		string action;
		while (validInput == false) {
			userInput = askForString("Would you like to walk to another catacomb (w), throw a grenade (g), look at your map (m), help (h) or quit (q): ");
			char userInputChar = tolower(userInput[0]);
			switch (userInputChar) {
			case 'w':
				// walk
				action = "move";
				validInput = true;
				break;
			case 'g':
				// throw grenade
				if (character->getGrenades() > 0) {
					action = "grenade";
					validInput = true;
				}
				else {
					cout << character->getName() << " has no more grenades left! Search the catacombs to find more grenades!\n";
				}
				break;
			case 'm':
				// display map
				displayMap();
				askForString("Press any key to stop looking at your map: ");
				// display UI again
				displayUI(character);
				break;
			case 'h':
				// help (display rules)
				system("CLS");
				displayRules();
				// display UI again
				displayUI(character);
				break;
			case 'q':
				// quit
				character->gameHasEnded();
				validInput = true;
				cout << "\nThanks for playing!\n\n";
				break;
			default:
				// Invalid input
				cout << "\nInvalid input. Please try again.\n";
			}
		}

		int targetCatacomb = 0;
		if (not character->getGameEnded()) {
			validInput = false;
			while (validInput == false) {
				if (action == "move") {
					userInput = askForString("Choose a direction to move in (possible directions listed above), look at your map (m), help (h) or quit (q): ");
				}
				else if (action == "grenade") {
					userInput = askForString("Choose a direction to throw at (possible directions listed above), look at your map (m), help (h) or quit (q): ");
				}
				char userInputChar = tolower(userInput[0]);

				switch (userInputChar) {
				case 'n':
					// Move to north catacomb
					if (currentCatacomb->getNorthCatacomb() != -1) {
						targetCatacomb = currentCatacomb->getNorthCatacomb();
						validInput = true;
					}
					else {
						cout << "\nNo exit in this direction. Please try again.";
					}
					break;
				case 'e':
					// Move to east catacomb
					if (currentCatacomb->getEastCatacomb() != -1) {
						targetCatacomb = currentCatacomb->getEastCatacomb();
						validInput = true;
					}
					else {
						cout << "\nNo exit in this direction. Please try again.";
					}
					break;
				case 's':
					// Move to south catacomb
					if (currentCatacomb->getSouthCatacomb() != -1) {
						targetCatacomb = currentCatacomb->getSouthCatacomb();
						validInput = true;
					}
					else {
						cout << "\nNo exit in this direction. Please try again.";
					}
					break;
				case 'w':
					// Move to west catacomb
					if (currentCatacomb->getWestCatacomb() != -1) {
						targetCatacomb = currentCatacomb->getWestCatacomb();
						validInput = true;
					}
					else {
						cout << "\nNo exit in this direction. Please try again.";
					}
					break;
				case 'm':
					// Display the map
					displayMap();
					askForString("Press any key to stop looking at your map: ");
					displayUI(character);
					break;
				case 'h':
					// Display rules
					system("CLS");
					displayRules();
					displayUI(character);
					break;
				case 'q':
					// Quit the game
					character->gameHasEnded();
					validInput = true;
					cout << "\nThanks for playing!\n\n";
					break;
				default:
					// Invalid input
					cout << "\nInvalid input. Please try again.\n";
				}
			}
		}
		if (not character->getGameEnded()) {
			// Execute the action
			if (action == "move") {
				// Remove one lantern energy cell
				character->setLanternEnergyCells(character->getLanternEnergyCells() - 1);

				// Move the character
				character->setCatacomb(targetCatacomb);
			}
			else if (action == "grenade") {
				// Throw grenade to targetCatacomb
				// Remove a grenade from the character
				character->setGrenades(character->getGrenades() - 1);

				// Check if Poggle is in that location
				if (catacombList[targetCatacomb]->getHazard() != nullptr) {
					if (catacombList[targetCatacomb]->getHazard()->getName() == "Poggle") {
						character->gameHasEnded();
						cout << "\n" << character->getName() << " blasts Poggle with a grenade! You win!\nThanks for playing!\n\n";
					}
				}
				if (character->getGameEnded() == false) {
					cout << "\nPoggle is not in that catacomb.\n";
					if (alertPoggle()) {
						cout << "Poggle is alerted and moves to an adjacent catacomb.\n";
					}
					else {
						cout << "Poggle is alerted but he stays in the same catacomb.\n";
					}

					if (catacombList[character->getCatacomb()]->getHazard() != nullptr) {
						if (catacombList[character->getCatacomb()]->getHazard()->getName() == "Poggle") {
							character->gameHasEnded();
							cout << "Poggle moved into the same catacomb as " << character->getName() << "! " << character->getName() << " is overcome by his minions!\n";
							cout << "Thanks for playing!\n\n";
						}
					}
					if (character->getGameEnded() == false) {
						askForString("Press any key to continue: ");
					}
				}
			}
		}
	}
}

bool displayUI(Character* character) {
	// This function displays the UI for the player
	// This functions returns true if the player is ready to play and returns false if the player needs to see the UI again (e.g. when a hazard moves the player).
	system("CLS");
	Catacomb* currentCatacomb = catacombList[character->getCatacomb()];
	// display title
	displayTitle();

	// display inventory
	cout << "Lantern energy cells: " << to_string(character->getLanternEnergyCells()) << "    Grenades: " << to_string(character->getGrenades()) << "\n";
	for (unsigned index = 0; index < character->getItems().size(); index++) {
		cout << character->getItems()[index]->getName() << "\n";
	}

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	// display location details
	cout << character->getName() + " is in " + currentCatacomb->getName() << "\n";
	cout << currentCatacomb->getDescription() << "\n";
	cout << "Possible directions: " << currentCatacomb->getExits() << "\n";

	// check for hazards in current location
	if (currentCatacomb->getHazard() != nullptr) {
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		// Manage hazard encounters
		if (currentCatacomb->getHazard()->getName() == "Poggle") {
			// Poggle
			character->gameHasEnded();
			cout << "You find yourself in Poggle's catacomb and are overcome by his minions!\nGame over!\n";
		}
		else if (currentCatacomb->getHazard()->getName() == "Hive Queen") {
			// Hive Queen
			// Check if player has an ultraviolet flashlight
			bool hasUltravioletFlashlight = false;
			for (unsigned index = 0; index < character->getItems().size(); index++) {
				if (character->getItems()[index]->getName() == "Ultraviolet flashlight") {
					hasUltravioletFlashlight = true;
					character->removeItem(new Item("Ultraviolet flashlight"));
					break;
				}
			}
			if (hasUltravioletFlashlight) {
				cout << "You stumble into the catacomb of Hive Queen Karina the Great and her horde of undead!\nFortunately, using your ultraviolet flashlight, you blind her in time for you to run into an adjacent catacomb!\nUnfortunately, you lose your ultraviolet flashlight in the process.\n\nYou rush off to a random adjacent catacomb.\n";
				// Remove the ultraviolet flashlight
				character->removeItem(new Item("Ultraviolet flashlight"));
				// Move character to a random adjacent catacomb.
				int randomMove = rand() % 4;
				bool validMove = false;
				while (validMove == false) {
					if (randomMove < 1 && currentCatacomb->getNorthCatacomb() != -1) {
						validMove = true;
						character->setCatacomb(currentCatacomb->getNorthCatacomb());
					}
					else if (randomMove < 2 && currentCatacomb->getEastCatacomb() != -1) {
						validMove = true;
						character->setCatacomb(currentCatacomb->getEastCatacomb());
					}
					else if (randomMove < 3 && currentCatacomb->getSouthCatacomb() != -1) {
						validMove = true;
						character->setCatacomb(currentCatacomb->getSouthCatacomb());
					}
					else if (randomMove <= 4 && currentCatacomb->getWestCatacomb() != -1) {
						validMove = true;
						character->setCatacomb(currentCatacomb->getWestCatacomb());
					}
					randomMove = rand() % 4;
				}

				askForString("Press any key to continue: ");
				return false;
			}
			else {
				character->gameHasEnded();
				cout << "You stumble into the catacomb of Hive Queen Karina the Great and her horde of undead!\nGame over!\n";
			}
		}
		else if (currentCatacomb->getHazard()->getName() == "Nest") {
			// Nest
			// Check if player has silent boots
			bool hasSilentBoots = false;
			for (unsigned index = 0; index < character->getItems().size(); index++) {
				if (character->getItems()[index]->getName() == "Silent boots") {
					hasSilentBoots = true;
					break;
				}
			}
			if (hasSilentBoots) {
				cout << "You pass a sleeping Geonosian nest and, because of your silent boots, you do not disturb them.\n";
			} else {
				cout << "You disturb a nest of sleeping Geonosians! They swarm you and carry you to another catacomb.\n";
				// Move the character to a random catacomb
				bool ok = false;
				int catacombIndex;
				Catacomb* catacomb = catacombList[0];
				// Check if the catacomb has a hazard. If it does, select another catacomb.
				while (ok == false) {
					catacombIndex = rand() % (catacombList.size());
					catacomb = catacombList[catacombIndex];
					if (catacomb->getHazard() == nullptr) {
						ok = true;
					}
				}
				// Set the character's location
				character->setCatacomb(catacombIndex);

				askForString("Press any key to continue: ");
				return false;
			}
		}
	}
	if (not character->getGameEnded()) {
		// Check for items in current location
		if (currentCatacomb->getItem() != nullptr) {
			// If there is an item, move it from the location to the inventory
			cout << "You have found an item: " << currentCatacomb->getItem()->getName() << "!\n";
			if (currentCatacomb->getItem()->getName() == "Lantern battery") {
				character->setLanternEnergyCells(character->getLanternEnergyCells() + 5);
				delete currentCatacomb->getItem();
			}
			else if (currentCatacomb->getItem()->getName() == "Extra grenade") {
				character->setGrenades(character->getGrenades() + 1);
				delete currentCatacomb->getItem();
			}
			else {
				character->addItem(currentCatacomb->getItem());
			}
			currentCatacomb->setItem(nullptr);
		}

		// Check for roaming characters in current location
		if (currentCatacomb->getRoamChar() != nullptr) {
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			if (currentCatacomb->getRoamChar()->getType() == "Scout Geonosian") {
				if (currentCatacomb->getRoamChar()->encounter() == "true") {
					if (alertPoggle()) {
						cout << "The Geonosian scout spots " << character->getName() << "! Poggle is alerted and moves to an adjacent catacomb.\n";
						if (catacombList[character->getCatacomb()]->getHazard() != nullptr) {
							if (catacombList[character->getCatacomb()]->getHazard()->getName() == "Poggle") {
								character->gameHasEnded();
								cout << "Poggle moved into the same catacomb as " << character->getName() << "! " << character->getName() << " is overcome by his minions!\n";
								cout << "Thanks for playing!\n\n";
							}
						}
					}
					else {
						cout << "The Geonosian scout spots " << character->getName() << "! Poggle is alerted but he stays in the same catacomb.\n";
					}
					// Move the scout to a random catacomb
					bool ok = false;
					int catacombIndex;
					Catacomb* catacomb = catacombList[0];
					// Check if the catacomb has a roaming character. If it does, select another catacomb.
					while (ok == false) {
						catacombIndex = rand() % (catacombList.size());
						catacomb = catacombList[catacombIndex];
						if (catacomb->getRoamChar() == nullptr) {
							ok = true;
						}
					}
					// Set the scout's location
					catacomb->setRoamChar(currentCatacomb->getRoamChar());
					currentCatacomb->setRoamChar(nullptr);
				}
				else {
					delete currentCatacomb->getRoamChar();
					currentCatacomb->setRoamChar(nullptr);
					cout << "The Geonosian scout spots " << character->getName() << "! But " << character->getName() << " kills the Geonosian scout before it is able to alert Poggle!\n";
				}
			}
			else if (currentCatacomb->getRoamChar()->getType() == "Thief Geonosian") {
				string outcome = currentCatacomb->getRoamChar()->encounter();
				if (outcome == "Nothing") {
					delete currentCatacomb->getRoamChar();
					currentCatacomb->setRoamChar(nullptr);
					cout << character->getName() << " manages to kill the Geonosian thief before it is able to steal anything!\n";
				}
				else {
					if (outcome == "Lantern energy cell") {
						character->setLanternEnergyCells(character->getLanternEnergyCells() - 1);
						cout << "A Geonosian thief steals a lantern energy cell and then runs away!\n";

					}
					else if (outcome == "Grenade") {
						character->setGrenades(character->getGrenades() - 1);
						cout << "A Geonosian thief steals a grenade and then runs away!\n";
					}
					// Move the thief to a random catacomb
					bool ok = false;
					int catacombIndex;
					Catacomb* catacomb = catacombList[0];
					// Check if the catacomb has a roaming character. If it does, select another catacomb.
					while (ok == false) {
						catacombIndex = rand() % (catacombList.size());
						catacomb = catacombList[catacombIndex];
						if (catacomb->getRoamChar() == nullptr) {
							ok = true;
						}
					}
					// Set the thief's location
					catacomb->setRoamChar(currentCatacomb->getRoamChar());
					currentCatacomb->setRoamChar(nullptr);
				}
			}
			else if (currentCatacomb->getRoamChar()->getType() == "Obi-Wan Kenobi") {
				delete currentCatacomb->getRoamChar();
				currentCatacomb->setRoamChar(nullptr);
				character->setHasKenobi(true);
				cout << character->getName() << " is now joined by Obi-Wan Kenobi, who can help in the hunt for Poggle!\n";
			}
		}


		// Display hints about nearby hazards
		bool alreadySplit = false;
		if (currentCatacomb->getNorthCatacomb() != -1) {
			if (catacombList[currentCatacomb->getNorthCatacomb()]->getHazard() != nullptr) {
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
				alreadySplit = true;
				cout << catacombList[currentCatacomb->getNorthCatacomb()]->getHazard()->getHint() + "\n";
				if (character->getHasKenobi()) {
					cout << "Obi-Wan Kenobi senses that this hazard is in the north catacomb.\n";
				}
			}
		}
		if (currentCatacomb->getEastCatacomb() != -1 && currentCatacomb->getEastCatacomb() != currentCatacomb->getNorthCatacomb()) {
			if (catacombList[currentCatacomb->getEastCatacomb()]->getHazard() != nullptr) {
				if (alreadySplit == false) {
					cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
					alreadySplit = true;
				}
				cout << catacombList[currentCatacomb->getEastCatacomb()]->getHazard()->getHint() + "\n";
				if (character->getHasKenobi()) {
					cout << "Obi-Wan Kenobi senses that this hazard is in the east catacomb.\n";
				}
			}
		}
		if (currentCatacomb->getSouthCatacomb() != -1 && currentCatacomb->getSouthCatacomb() != currentCatacomb->getEastCatacomb()) {
			if (catacombList[currentCatacomb->getSouthCatacomb()]->getHazard() != nullptr) {
				if (alreadySplit == false) {
					cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
					alreadySplit = true;
				}
				cout << catacombList[currentCatacomb->getSouthCatacomb()]->getHazard()->getHint() + "\n";
				if (character->getHasKenobi()) {
					cout << "Obi-Wan Kenobi senses that this hazard is in the south catacomb.\n";
				}
			}
		}
		if (currentCatacomb->getWestCatacomb() != -1 && currentCatacomb->getWestCatacomb() != currentCatacomb->getNorthCatacomb() && currentCatacomb->getWestCatacomb() != currentCatacomb->getSouthCatacomb()) {
			if (catacombList[currentCatacomb->getWestCatacomb()]->getHazard() != nullptr) {
				if (alreadySplit == false) {
					cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
					alreadySplit = true;
				}
				cout << catacombList[currentCatacomb->getWestCatacomb()]->getHazard()->getHint() + "\n";
				if (character->getHasKenobi()) {
					cout << "Obi-Wan Kenobi senses that this hazard is in the west catacomb.\n";
				}
			}
		}

		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	}
	return true;
}


void displayMap() {
	// This function loads the map from a txt file and displays it.
	ifstream fileToRead("map.txt");

	if (fileToRead.is_open()) {
		string line = "";
		while (!fileToRead.eof()) {
			getline(fileToRead, line);
			if (line != "") {
				cout << line << "\n";
			}
		}
	}
	fileToRead.close();
}

bool alertPoggle() {
	// This function alerts Poggle
	// This function returns true if Poggle moves and returns false if Poggle stays in the same catacomb.
	int randomNumber = rand() % 4;
	if (randomNumber <= 2) {
		// Poggle moves
		// Find Poggle
		Catacomb* catacomb = catacombList[0];
		Hazard* poggle = new Poggle();
		for (unsigned index = 0; index < catacombList.size(); index++) {
			catacomb = catacombList[index];
			if (catacomb->getHazard() != nullptr) {
				if (catacomb->getHazard()->getName() == "Poggle") {
					poggle = catacomb->getHazard();
					break;
				}
			}
		}
		// Move Poggle
		int randomMove = rand() % 4;
		bool validMove = false;
		Catacomb* newCatacomb = nullptr;
		while (validMove == false) {
			if (randomMove < 1 && catacomb->getNorthCatacomb() != -1) {
				validMove = true;
				poggle->setCatacomb(catacomb->getNorthCatacomb());
				catacomb->setHazard(nullptr);
				catacombList[catacomb->getNorthCatacomb()]->setHazard(poggle);
				newCatacomb = catacombList[catacomb->getNorthCatacomb()];
			}
			else if (randomMove < 2 && catacomb->getEastCatacomb() != -1) {
				validMove = true;
				poggle->setCatacomb(catacomb->getEastCatacomb());
				catacomb->setHazard(nullptr);
				catacombList[catacomb->getEastCatacomb()]->setHazard(poggle);
				newCatacomb = catacombList[catacomb->getEastCatacomb()];
			}
			else if (randomMove < 3 && catacomb->getSouthCatacomb() != -1) {
				validMove = true;
				poggle->setCatacomb(catacomb->getSouthCatacomb());
				catacomb->setHazard(nullptr);
				catacombList[catacomb->getSouthCatacomb()]->setHazard(poggle);
				newCatacomb = catacombList[catacomb->getSouthCatacomb()];
			}
			else if (randomMove < 4 && catacomb->getWestCatacomb() != -1) {
				validMove = true;
				poggle->setCatacomb(catacomb->getWestCatacomb());
				catacomb->setHazard(nullptr);
				catacombList[catacomb->getWestCatacomb()]->setHazard(poggle);
				newCatacomb = catacombList[catacomb->getWestCatacomb()];
			}
		}
		if (newCatacomb != nullptr && testingMode) {
			cout << "TESTING MODE: Poggle moves to " << newCatacomb->getName() << endl;
		}
		return true;
	}
	else {
		// Poggle stays where he is
		return false;
	}
}

void moveRoamChars() {
	// This function moves the roaming characters to adjacent catacombs.
	// It is possible for roaming characters to move more than once or not at all.
	vector<Catacomb*>::iterator iter;
	bool changesMade = false;
	for (iter = catacombList.begin(); iter != catacombList.end(); iter++) {
		Catacomb* catacomb = *iter;
		Catacomb* newCatacomb = nullptr;
		if (catacomb->getRoamChar() != nullptr) {
			// Move roaming character to a random adjacent catacomb.
			int randomMove = rand() % 4;
			if (randomMove < 1 && catacomb->getNorthCatacomb() != -1) {
				if (catacombList[catacomb->getNorthCatacomb()]->getRoamChar() == nullptr) {
					catacombList[catacomb->getNorthCatacomb()]->setRoamChar(catacomb->getRoamChar());
					newCatacomb = catacombList[catacomb->getNorthCatacomb()];
					catacomb->setRoamChar(nullptr);
					changesMade = true;
				}
			}
			else if (randomMove < 2 && catacomb->getEastCatacomb() != -1) {
				if (catacombList[catacomb->getEastCatacomb()]->getRoamChar() == nullptr) {
					catacombList[catacomb->getEastCatacomb()]->setRoamChar(catacomb->getRoamChar());
					newCatacomb = catacombList[catacomb->getEastCatacomb()];
					catacomb->setRoamChar(nullptr);
					changesMade = true;
				}
			}
			else if (randomMove < 3 && catacomb->getSouthCatacomb() != -1) {
				if (catacombList[catacomb->getSouthCatacomb()]->getRoamChar() == nullptr) {
					catacombList[catacomb->getSouthCatacomb()]->setRoamChar(catacomb->getRoamChar());
					newCatacomb = catacombList[catacomb->getSouthCatacomb()];
					catacomb->setRoamChar(nullptr);
					changesMade = true;
				}
			}
			else if (randomMove <= 4 && catacomb->getWestCatacomb() != -1) {
				if (catacombList[catacomb->getWestCatacomb()]->getRoamChar() == nullptr) {
					catacombList[catacomb->getWestCatacomb()]->setRoamChar(catacomb->getRoamChar());
					newCatacomb = catacombList[catacomb->getWestCatacomb()];
					catacomb->setRoamChar(nullptr);
					changesMade = true;
				}
			}
		}
		if (newCatacomb != nullptr && testingMode) {
			cout << "TESTING MODE: " << newCatacomb->getRoamChar()->getType() << " moves to " << newCatacomb->getName() << endl;
		}
	}
	if (testingMode && changesMade) {
		askForString("Press any key to continue: ");
	}
}

bool checkGrenades(Character* character) {
	// This function checks if there are any grenades left in the game
	if (character->getGrenades() > 0) {
		return true;
	}
	else {
		vector<Catacomb*>::iterator iter;
		for (iter = catacombList.begin(); iter != catacombList.end(); iter++) {
			Catacomb* catacomb = *iter;
			if (catacomb->getItem() != nullptr) {
				if (catacomb->getItem()->getName() == "Extra grenade") {
					return true;
				}
			}
		}
		return false;
	}
}

string askForString(string question) {
	// This function gets user input for string inputs
	cin.clear();
	string userInput = "";
	cout << "\n" + question;
	while (userInput == "") {
		getline(cin, userInput);
	}
	return userInput;
}

void cleanMemory() {
	// This function is called at the end of the game.
	// This function manages the memory by deleting all the pointers.

	// Clean catacombs
	vector<Catacomb*>::iterator iter;
	for (iter = catacombList.begin(); iter != catacombList.end(); iter++) {
		Catacomb* catacomb = *iter;
		// Remove hazard from each catacomb
		if (catacomb->getHazard() != nullptr) {
			delete catacomb->getHazard();
			catacomb->setHazard(nullptr);
		}
		// Remove item from each catacomb
		if (catacomb->getItem() != nullptr) {
			delete catacomb->getItem();
			catacomb->setItem(nullptr);
		}
		// Remove roaming character from each catacomb
		if (catacomb->getRoamChar() != nullptr) {
			delete catacomb->getRoamChar();
			catacomb->setRoamChar(nullptr);
		}
		// Remove the catacomb itself
		delete catacomb;
	}

	// Clean the character
	for (int index = 0; index < character->getItems().size(); index++) {
		delete character->getItems()[index];
	}
	delete character;

}