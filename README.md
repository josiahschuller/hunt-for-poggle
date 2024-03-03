# The Hunt for Poggle the Lesser

This game was written for a university project in semester 2 2021.

For game rules, see page 12 of `A3-JosiahSchuller.pdf`.


# University project information

The project is based on the game "Hunt the Wumpus".

My chosen theme is Star Wars. As explained in the game rules, the game is set in the cave system underground an ancient Geonosian temple.
Some of the classes are renamed to fit the theme:
Player has been renamed to Character.
Location has been renamed to Catacomb.
Wumpus has been renamed to Poggle.
Bottomless Pit has been renamed to HiveQueen.
Super Bats has been renamed to Nest.
Shooting arrows has been renamed to throwing grenades.
Oil has been renamed to light energy cells.

## Extra functionality implemented:

- The player can select a skill level: At the start of the game, the player can choose between padawan, jedi knight and jedi master skill difficulties. These skill difficulties affect the number of items, hazards and roaming characters that spawn.
- Add theme to game: see below for explanation
- Player can find items while exploring game locations: The player will collect these items by travelling into catacombs that contain items.
- Create roaming opponents that the player encounters while exploring the game locations

## Roaming opponents:

RoamChar is the main class for the roaming characters.
Thief, Scout and ObiWanKenobi are child classes of RoamChar and are the roaming characters the player will see in game.

## Other notes:

End game condition of running out of grenades is replaced with the condition that the character has run out of grenades AND there are no more extra grenades to collect from the catacombs.

## Testing tools:

In Application.h line 23, set testing mode to true. This will enable extra cout statements that are useful for testing.
