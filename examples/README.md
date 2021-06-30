# Pacman

* Author: Kirill Alekhnovich

## Basic functionality

1. Basic rules: collecting bonuses, coins (dots), cherries, teleports, etc.
2. Several types of AI ghosts are implemented.
3. Map can be configured from a file.
4. Configurable difficulty of the game from the file (speed of ghosts, duration of individual game modes, probability of adding a new bonus to the map, etc.)
5. Scalable ghost difficulty.

## Advanced functionality

* The game includes a main menu and a post-game menu.
* During the game, the number of points is displayed.
* The game remembers achieved high score.

## Polymorphism usages

1. Moving objects. Every moving object (ghost, pacman) is in motion. But each sprite moves differently.
2. Ghosts. Ghosts have pretty similar behavior, but some things differ (for example, they have different target on the map).
3. Bonuses. Each bonus should give Pacman a different number of points.