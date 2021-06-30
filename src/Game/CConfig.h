#pragma once
#include <iostream>
/**
* @file CConfig.h
* @brief Setting configurations from file
*/
class CConfig {
public:
    /**
     * @brief Reading parameters from a file
     * @return Boolean success variable
     */
    bool setup();
    /**
    * @brief Check if parameter value is out of range or not and also check if we have enough parameters
    * @return Return boolean variable
    */
    bool check() const;

    int mapWidth{}, mapHeight{}, width{}, height{}, tileSize = 64; // dimensions
    int ghostsSpeed{}, redStartX{}, redStartY{}; // ghosts configs
    int pacmanStartX{}, pacmanStartY{}, pacmanLives{}, pacmanSpeed{}; // pacman configs
    int detentionTime{}, frightenedTime{}, chaseTime{}, scatterTime{}; // timers
    int shift{}, highScore{}, bonusSpawnChance{}; // others
    float scale{};
};