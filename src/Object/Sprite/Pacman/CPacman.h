#pragma once
#include "../CMovingObject.h"
#include "../../../Game/CConfig.h"
#include <SDL2/SDL_image.h>
#include <cmath>

/**
* @brief Pacman behaviour
*/
class CPacman : public CMovingObject{
public:
    /**
     * @brief Constructor for Pacman
     */
    CPacman() : CMovingObject(), currentDirection(Direction::NONE), nextDirection(Direction::NONE) {}
    /**
     * @brief Checking collision with walls
     * @param map Game's map
     * @return Boolean depending on does Pacman collide with wall or not
     */
    bool wallCollision(CMap &map);
    /**
     * @brief Eating bonuses
     * @param map Game's map
     * @return Number of points that have to be given to player
     */
    int foodCollision(CMap &map) const;
    /**
     * @brief Moving Pacman on the map
     * @param renderer App's renderer
     * @param map Game's map
     */
    void move(SDL_Renderer *renderer, CMap &map) override;
    /**
     * @brief Setting Pacman's model depending on mode and timer
     * @param tmp Pacman's rectangle
     */
    void setModelToDraw(SDL_Rect &tmp) override;
    /**
     * @brief Setting Pacman's direction
     * @param direction New direction
     * @param map Game's map
     */
    void setDirection(Direction direction, CMap &map) override;
    /**
     * @brief Solving predeclared direction and changing current direction if necessary
     * @param map Game's map
     */
    void preDeclaredSolver(CMap &map);
    /**
     * @brief Getting current direction
     * @return Current direction
     */
    Direction getCurrentDirection() const { return currentDirection; }
private:
    Direction currentDirection;
    Direction nextDirection;
    CTilePos newPosCurrent;
};
