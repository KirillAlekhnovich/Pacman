#include "CGhost.h"

using namespace std;

Direction CGhost::changeDirection(CMap &map) {
    /* Correcting x if prisoned to get out */
    if (prisoned) {
        if (position.x / config->tileSize < config->redStartX)
            return Direction::RIGHT;
        if (position.x / config->tileSize > config->redStartX)
            return Direction::LEFT;
        return Direction::UP;
    }
    int up, down, left, right;
    CTilePos rightTile, leftTile, upTile, downTile;
    /* Finding shortest direction to target */
    upTile = {position.x / config->tileSize, position.y / config->tileSize - 1};
    up = calculateHypotenuse(upTile, destination / config->tileSize);
    downTile = {position.x / config->tileSize, position.y / config->tileSize + 1};
    down = calculateHypotenuse(downTile, destination / config->tileSize);
    leftTile = {position.x / config->tileSize - 1, position.y / config->tileSize};
    left = calculateHypotenuse(leftTile, destination / config->tileSize);
    rightTile = {position.x / config->tileSize + 1, position.y / config->tileSize};
    right = calculateHypotenuse(rightTile, destination / config->tileSize);
    Direction tmp = Direction::NONE;
    switch (currentDirection) { // in every intersection we have to check 3 directions (because ghosts can't go back)
        case Direction::UP:
            if (map.getMap()[rightTile.y - config->shift][rightTile.x]->canStepOn())
                tmp = Direction::RIGHT;
            if (map.getMap()[leftTile.y - config->shift][leftTile.x]->canStepOn())
                if (left < right || tmp == Direction::NONE)
                    tmp = Direction::LEFT;
            if (map.getMap()[upTile.y - config->shift][upTile.x]->canStepOn())
                if ((up < left && tmp == Direction::LEFT) || (up < right && tmp == Direction::RIGHT) ||
                    tmp == Direction::NONE)
                    tmp = Direction::UP;
            return tmp;
        case Direction::DOWN:
            if (map.getMap()[rightTile.y - config->shift][rightTile.x]->canStepOn())
                tmp = Direction::RIGHT;
            if (map.getMap()[leftTile.y - config->shift][leftTile.x]->canStepOn())
                if (left < right || tmp == Direction::NONE)
                    tmp = Direction::LEFT;
            if (map.getMap()[downTile.y - config->shift][downTile.x]->canStepOn())
                if ((down < left && tmp == Direction::LEFT) || (down < right && tmp == Direction::RIGHT) ||
                    tmp == Direction::NONE)
                    tmp = Direction::DOWN;
            return tmp;
        case Direction::LEFT:
            if (map.getMap()[leftTile.y - config->shift][leftTile.x]->canStepOn())
                tmp = Direction::LEFT;
            if (map.getMap()[downTile.y - config->shift][downTile.x]->canStepOn())
                if (down < left || tmp == Direction::NONE)
                    tmp = Direction::DOWN;
            if (map.getMap()[upTile.y - config->shift][upTile.x]->canStepOn())
                if ((up < left && tmp == Direction::LEFT) || (up < down && tmp == Direction::DOWN) ||
                    tmp == Direction::NONE)
                    tmp = Direction::UP;
            return tmp;
        case Direction::RIGHT:
            if (map.getMap()[rightTile.y - config->shift][rightTile.x]->canStepOn())
                tmp = Direction::RIGHT;
            if (map.getMap()[upTile.y - config->shift][upTile.x]->canStepOn())
                if (up < right || tmp == Direction::NONE)
                    tmp = Direction::UP;
            if (map.getMap()[downTile.y - config->shift][downTile.x]->canStepOn())
                if ((down < right && tmp == Direction::RIGHT) || (down < up && tmp == Direction::UP) ||
                    tmp == Direction::NONE)
                    tmp = Direction::DOWN;
            return tmp;
        case Direction::NONE:
            break;
    }
    return Direction::NONE;
}

void CGhost::move(SDL_Renderer *renderer, CMap &map) {
    Direction oldDir;
    oldDir = currentDirection;
    newPosition = position;

    if (prisoned && destination == position) { // if ghost got out of a prison
        prisoned = false;
        inGates = false;
    }

    if (collisionCorrect(currentDirection)) {
        stepOnTeleport(map);
        return;
    }

    if (position.x % config->tileSize == 0 && position.y % config->tileSize == 0) {
        if (intersectionCheck(map))
            currentDirection = changeDirection(map); // changing direction if only ghost is at intersection
    }

    newPosition = position.move(currentDirection, speed);

    if (prisoned && currentDirection != Direction::NONE) {
        position = newPosition; // allowing ghosts to get out of prison
        return;
    }
    if (!map.getMap()[newPosition.y / config->tileSize - config->shift][newPosition.x / config->tileSize]->canStepOn()) {
        currentDirection = oldDir;
        return;
    }
    position = newPosition;
    if (position.x % config->tileSize == 0 && position.y % config->tileSize == 0)
        stepOnTeleport(map); // check if current tile is teleport if we are at the beginning of the tile
}

bool CGhost::intersectionCheck(CMap &map) const {
    switch (currentDirection) {
        case Direction::UP:
        case Direction::DOWN:
            if ((map.getMap()[position.y / config->tileSize - config->shift][position.x / config->tileSize +
                                                                             1]->canStepOn())
                || (map.getMap()[position.y / config->tileSize - config->shift][position.x / config->tileSize -
                                                                                1]->canStepOn()))
                return true; // we can return true if one of side directions does not contain wall
            break;
        case Direction::LEFT:
        case Direction::RIGHT:
            if ((map.getMap()[position.y / config->tileSize - config->shift + 1][position.x /
                                                                                 config->tileSize]->canStepOn())
                || (map.getMap()[position.y / config->tileSize - config->shift - 1][position.x /
                                                                                    config->tileSize]->canStepOn()))
                return true;
            break;
        case Direction::NONE:
            break;
    }
    return false;
}

int CGhost::calculateHypotenuse(CTilePos current, CTilePos dest) {
    int a, b, c; // Pythagoras' Theorem
    a = abs(current.y - dest.y);
    b = abs(current.x - dest.x);
    c = a * a + b * b;
    return c;
}

void CGhost::setModelToDraw(SDL_Rect &tmp) {
    /* Switching object's model in determined interval of time */
    if (currentDirection != Direction::NONE) {
        if (updateTimer == 15) {
            if (tmp.x == 32)
                tmp.x = 0;
            else
                tmp.x += 32;
            updateTimer = 0;
        }
        updateTimer++;
    }

    /* Changing row of sheet */
    if (*gameMode == GameMode::FRIGHTENED && (!prisoned || inGates)) {
        if ((int) SDL_GetTicks() - frightenedTimer >= config->frightenedTime - 2000)
            tmp.y = 128; // blinking at the end of frightened time
        else
            tmp.y = 160;
    } else {
        frightenedTimer = 0;
        switch (currentDirection) {
            case Direction::UP:
                tmp.y = 32;
                break;
            case Direction::DOWN:
                tmp.y = 96;
                break;
            case Direction::LEFT:
                tmp.y = 64;
                break;
            case Direction::RIGHT:
                tmp.y = 0;
                break;
            case Direction::NONE:
                tmp.y = 64;
                tmp.x = 0;
                break;
        }
    }
}

void CGhost::reset(CTilePos target) {
    speed = config->ghostsSpeed;
    position = startingPos * config->tileSize;
    destination = target * config->tileSize;
    prisoned = true;
    currentDirection = Direction::LEFT;
}