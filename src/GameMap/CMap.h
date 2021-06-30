#pragma once
#include <SDL2/SDL.h>
#include "../Object/CObject.h"
#include "../Game/CConfig.h"
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include <ctime>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <iomanip>

using namespace std;

/**
* @brief Methods used to implement map
*/
class CMap {
public:
    /**
     * @brief Loading map from file
     * @param renderer App's renderer
     * @param setup Game's configurations
     * @return Boolean success variable
     */
    bool loadMap(SDL_Renderer *renderer, CConfig *setup); /* Loading map from file */
    /**
     * @brief Drawing map
     * @param renderer App's renderer
     * @param bonusCount Number of bonuses
     */
    void draw(SDL_Renderer *renderer, int bonusCount);
    /**
     * @brief Bonus generator
     * @param level Game level
     * @param renderer App's renderer
     */
    void generateBonus(int level, SDL_Renderer *renderer);
    /**
     * @brief Drawing Pacman lives and bonus count at footer
     * @param renderer App's renderer
     * @param bonusCount Number of bonuses
     */
    void drawFooter(SDL_Renderer *renderer, int bonusCount);
    /**
     * @brief Counter for bonuses in the footer
     * @param renderer App's renderer
     * @param bonusCount Number of bonuses
     */
    void bonusCounter(SDL_Renderer *renderer, int bonusCount);
    /**
     * @brief Clearing textures
     */
    void quit();
    /**
     * @brief Getting tile
     * @param x Dimension x
     * @param y Dimension y
     * @return Object of needed tile
     */
    CObject getTile(int x, int y) const { return *map[y][x]; }
    /**
     * @brief Map
     * @return All the fields of the map
     */
    const vector<vector<CObject*>> &getMap() const { return map; }
    /**
     * @brief Getter for food
     * @return Food count
     */
    int getFoodCount() const { return foodCount; }
    /**
     * @brief Getter for teleports
     * @return Teleports positions
     */
    const pair<CTilePos, CTilePos> &getTeleports() const { return teleports; }
    /**
     * @brief Setting food count
     * @param c Food count
     */
    void setFoodCount(int c)  { foodCount = c; }
    /**
     * @brief Setting an object into exact position
     * @param x Dimension x
     * @param y Dimension y
     * @param object Object that has to be set
     */
    void setTile(int x, int y, CObject object) { map[y][x] = &object; }
    /**
     * @brief Checking if mapWidth and mapHeight is correct
     * @return Correct or not
     */
    bool checkDimensionsConfig();
private:
    CConfig *config;
    int width, height, foodCount = 0;
    vector<vector<CObject*>> map;
    pair<CTilePos, CTilePos> teleports;
};
