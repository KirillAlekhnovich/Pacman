#include "CPacman.h"

using namespace std;

void CPacman::move(SDL_Renderer *renderer, CMap &map) {
    newPosCurrent = position;
    /* Correcting collision at each tile */
    if (collisionCorrect(currentDirection)){
        stepOnTeleport(map); // check tp collision after correcting position
        return;
    }

    /* If we are at the beginning of the tile -> try to move in previously declared direction */
    if (position.x % config->tileSize == 0 && position.y % config->tileSize == 0)
        preDeclaredSolver(map);

    newPosCurrent = position.move(currentDirection, speed); // move Pacman in current direction

    if (!wallCollision(map)) // change position if there is no wall in next tile
        position = newPosCurrent;

    if (position.x % config->tileSize == 0 && position.y % config->tileSize == 0) // check tp collision
        stepOnTeleport(map);
}

void CPacman::setDirection(Direction inputDirection, CMap &map) {
    CTilePos newPos = position;

    /* Changing direction on non-opposite only if we're at the beginning of the tile */
    if (!position.oppositeDirection(currentDirection, inputDirection)) {
        if (position.x % config->tileSize != 0 || position.y % config->tileSize != 0) {
            nextDirection = inputDirection;
            return;
        }
    }

    /* Checking if next tile contains wall */
    switch (inputDirection) {
        case Direction::UP:
            newPos.y -= config->tileSize;
            break;
        case Direction::DOWN:
            newPos.y += config->tileSize;
            break;
        case Direction::LEFT:
            newPos.x -= config->tileSize;
            break;
        case Direction::RIGHT:
            newPos.x += config->tileSize;
            break;
        case Direction::NONE:
            break;
    }

    /* Changing direction only if next tile won't contain wall */
    if (!map.getMap()[newPos.y / config->tileSize - config->shift][newPos.x / config->tileSize]->canStepOn()) {
        /* If input direction points at wall we're saving it for next intersection */
        if (inputDirection != currentDirection &&
            !position.oppositeDirection(currentDirection, inputDirection))
            nextDirection = inputDirection;
        return;
    }

    /* If no walls has been found on the way set current direction as input direction and clear nextDirection if
     * current direction has been changed */
    if (currentDirection != inputDirection) {
        currentDirection = inputDirection;
        nextDirection = Direction::NONE;
    }
}

bool CPacman::wallCollision(CMap &map) {
    /* Shifting depending on direction to check if next tile contains wall */
    CTilePos shift = newPosCurrent;
    switch (currentDirection) {
        case Direction::UP:
            break;
        case Direction::DOWN:
            shift.y += config->tileSize;
            break;
        case Direction::LEFT:
            break;
        case Direction::RIGHT:
            shift.x += config->tileSize;
            break;
        case Direction::NONE:
            break;
    }

    /* If next tile is wall */
    if (!map.getMap()[shift.y / config->tileSize - config->shift][shift.x / config->tileSize]->canStepOn())
        return !collisionCorrect(currentDirection); // correcting position if we have reached wall
    return false;
}

int CPacman::foodCollision(CMap &map) const{
    if (map.getMap()[position.y / config->tileSize - config->shift][position.x / config->tileSize]->getId() == 0)
        return 0;
    map.getMap()[position.y / config->tileSize - config->shift][position.x / config->tileSize]->setSource(0,0,0,0);
    map.getMap()[position.y / config->tileSize - config->shift][position.x / config->tileSize]->setId(0);
    int tmp = map.getMap()[position.y / config->tileSize - config->shift][position.x / config->tileSize]->eat();
    if (tmp != 0)
        map.setFoodCount(map.getFoodCount() - 1);
    return tmp;
}

void CPacman::setModelToDraw(SDL_Rect &tmp) {
    if (currentDirection != Direction::NONE){
        if (updateTimer == 10){
            if (tmp.x == 66)
                tmp.x = 0;
            else
                tmp.x += 33;
            updateTimer = 0;
        }
        updateTimer++; // pacman will open mouth after 10 iterations
    }

    /* Changing row of pacman sheet */
    switch (currentDirection) {
        case Direction::UP:
            tmp.y = 32;
            break;
        case Direction::DOWN:
            tmp.y = 64;
            break;
        case Direction::LEFT:
            tmp.y = 96;
            break;
        case Direction::RIGHT:
            tmp.y = 0;
            break;
        case Direction::NONE:
            tmp.y = 0;
            tmp.x = 33;
            break;
    }
}

void CPacman::preDeclaredSolver(CMap &map) {
    CTilePos newPosPrevious = position; // predeclared position (pressed key while wall was on it's way)
    bool nextTileWall = false;
    /* Don't move if pre-declared direction is none */
    if (nextDirection == Direction::NONE)
        nextTileWall = true;
    /* Else check if next tile contains wall */
    if (!nextTileWall) {
        switch (nextDirection) {
            case Direction::UP:
                newPosPrevious.y -= config->tileSize;
                break;
            case Direction::DOWN:
                newPosPrevious.y += config->tileSize;
                break;
            case Direction::LEFT:
                newPosPrevious.x -= config->tileSize;
                break;
            case Direction::RIGHT:
                newPosPrevious.x += config->tileSize;
                break;
            case Direction::NONE:
                break;
        }
        if (!map.getMap()[newPosPrevious.y / config->tileSize - config->shift][newPosPrevious.x / config->tileSize]->canStepOn())
            nextTileWall = true;
    }

    if (!nextTileWall) { // turn if tile in predeclared direction is not a wall and reset nextDirection
        currentDirection = nextDirection;
        nextDirection = Direction::NONE;
    }
}