#pragma once

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "../Object/Sprite/Pacman/CPacman.h"
#include "../GameMap/CMap.h"
#include "../GameMap/CScoreBoard.h"
#include "CConfig.h"
#include "../Object/Sprite/Ghost/CRed.h"
#include "CGameMode.h"
#include "../Object/Sprite/Ghost/COrange.h"
#include "../Object/Sprite/Ghost/CPink.h"
#include "../Object/Sprite/Ghost/CBlue.h"
#include "CMainMenu.h"
#include "CGameOverMenu.h"
#include <iostream>
#include <ctime>

/**
* @brief Realistaion of game process
*/
class CGame {
public:
    /**
     * @brief Initializing everything in gameplay
     * @param setup Importing game configurations
     * @param ren Importing window renderer
     * @param win Importing window
     * @return Returning false if something went wrong
     */
    bool run(CConfig *setup, SDL_Renderer *ren, SDL_Window *win);
    /**
     * @brief Reading input keys and processing it
     * @return Returning false if window has to be close, else - true
     */
    bool input();
    /**
     * @brief Quitting the game
     */
    void quit();
    /**
     * @brief Moving to the next level and changing configurations
     */
    void nextLvl();
    /**
     * @brief Initializing sprites
     */
    void initSprites();
    /**
     * @brief Processing game over screen if pacman has died *pacmanLives* times
     * @return If player wants to play more - return false, else - return true
     */
    bool gameOver() const;
    /**
     * @brief Resetting mode timers and changing mode if it's needed
     */
    void modeTimers();
    /**
     * @brief Drawing all the textures in current state
     */
    void update();
    /**
     * @brief Resolving Pacman's eating
     */
    void eat();
    /**
     * @brief Checking if ghosts collide with Pacman
     * @param ghost Each ghost one by one
     */
    void spritesCollision(CGhost *ghost);
    /**
     * @brief If mode is frightened and ghost has to be eaten
     * @param ghost Each ghost one by one
     */
    void ghostEaten(CGhost *ghost);
    /**
     * @brief Pacman is eaten by ghosts, resetting the game
     */
    void pacmanEaten() const;
    /**
     * @brief Trying to get ghosts out of prison
     * @param ghost Each ghost one by one
     * @param additionalWait Ghosts shouldn't leave prison at the same time
     */
    void outOfPrison(CGhost *ghost, int additionalWait);
    /**
     * @brief Boolean constant that shows if player wants to play one more game
     * @return Bool depending on player's choice
     */
    bool isRestart() const { return restart; }
private:
    CConfig *config{};
    int level = 1;
    SDL_Window *window{};
    SDL_Renderer *renderer{};
    SDL_Rect pacmanPos{};
    CMap map;
    CPacman *pacman{};
    CScoreBoard scoreBoard{};
    GameMode gameMode;
    vector <CGhost*> ghosts;
    int score = 0, bonusCounter = 0, highScore = 0;
    int frightenedStart = 0, scatterStart = 0, chaseStart = 0, frightenedEaten = 0, roundStart = 0;
    bool restart = false;
};
