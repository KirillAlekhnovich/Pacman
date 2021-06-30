#pragma once

#include "../CObject.h"
#include "Direction.h"
#include "../../GameMap/CMap.h"

/**
* @brief General methods for both Pacman and ghosts
*/
class CMovingObject : public CObject {
public:
    /**
     * @brief Constructor for moving object
     */
    CMovingObject() : CObject(), currentDirection(Direction::NONE) {}
    /**
     * @brief Moving an object
     * @param renderer App's renderer
     * @param map Game's map
     */
    virtual void move(SDL_Renderer *renderer, CMap &map) = 0;
    /**
     * @brief Setting model to draw
     * @param tmp Object's rectangle
     */
    virtual void setModelToDraw(SDL_Rect &tmp) = 0;
    /**
     * @brief Setting direction
     * @param direction New direction
     * @param map Game's map
     */
    virtual void setDirection(Direction direction, CMap &map) = 0;
    /**
     * @brief Preparing to draw an object, setting position and model
     * @param renderer App's renderer
     */
    void drawPreparation(SDL_Renderer *renderer);
    /**
     * @brief Initializing new moving object
     * @param spriteSize Size of sprite
     * @param setup Game's configurations
     */
    void init(int spriteSize, CConfig *setup);
    /**
     * @brief Solving teleports logic
     * @param map Game map
     * @return Returning boolean that shows if sprite has been teleported
     */
    bool stepOnTeleport(CMap &map);
    /**
     * @brief Correcting collision at each tile
     * @param direction Current direction
     * @return Boolean that shows if collision has been corrected
     */
    bool collisionCorrect(Direction &direction);
    /**
     * @brief Setting sprite's speed
     * @param s Sprite's speed
     */
    void setSpeed(int s) { speed = s; }
protected:
    int speed{}, updateTimer = {};
    Direction currentDirection;
};
