/**************************************************
 Project: JosiahSchullerA3
 Author: Josiah Schuller
 Purpose: Application Header File
**************************************************/
#ifndef APPLICATION_H
#define APPLICATION_H
#include <iostream>
#include <string>
#include "Character.h"
#include "Poggle.h"
#include "HiveQueen.h"
#include "Nest.h"
#include "Scout.h"
#include "Thief.h"
#include "ObiWanKenobi.h"
#include "fstream"
#include <vector>
using namespace std;

Character* character;
vector<Catacomb*> catacombList;
bool testingMode = false;

int main();
void displayTitle();
void displayRules();
void setupGame();
void setupCatacombs();
void assignHazard(Hazard* hazard);
void assignItem(Item* item);
void assignRoamChar(RoamChar* roamChar);
void playGame();
void userTurn(Character* character);
bool displayUI(Character* character);
void displayMap();
bool alertPoggle();
void moveRoamChars();
bool checkGrenades(Character* character);
string askForString(string question);
void cleanMemory();

#endif