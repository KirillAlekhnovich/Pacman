#include "CMovingObject.h"

using namespace std;

bool CMovingObject::stepOnTeleport(CMap &map) {
    /* Shifting map because of scoreboard and to avoid getting out of map */
    CTilePos tmpFirst, tmpSecond;
    tmpFirst = map.getTeleports().first;
    tmpSecond = map.getTeleports().second;
    tmpFirst.y += config->shift * config->tileSize;
    tmpSecond.y += config->shift * config->tileSize;
    /* Changing object's position */
    if (position == tmpFirst) {
        tmpSecond.x -= 1;
        position = tmpSecond;
        return true;
    }
    else if (position == tmpSecond) {
        tmpFirst.x += 1;
        position = tmpFirst;
        return true;
    }
    return false;
}

bool CMovingObject::collisionCorrect(Direction &direction) {
    switch (direction) {
        case Direction::UP:
            /* If there are less pixels left till the new tile than our speed then set next tile as position */
            if (position.y % config->tileSize != 0 && position.y % config->tileSize <= speed) {
                position = position.move(direction, position.y % config->tileSize);
                return true;
            }
            break;
        case Direction::DOWN:
            if (position.y % config->tileSize != 0 && config->tileSize - (position.y % config->tileSize) <= speed) {
                position = position.move(direction, config->tileSize - (position.y % config->tileSize));
                return true;
            }
            break;
        case Direction::LEFT:
            if (position.x % config->tileSize != 0 && position.x % config->tileSize <= speed) {
                position = position.move(direction, position.x % config->tileSize);
                return true;
            }
            break;
        case Direction::RIGHT:
            if (position.x % config->tileSize != 0 && config->tileSize - (position.x % config->tileSize) <= speed) {
                position = position.move(direction, config->tileSize - (position.x % config->tileSize));
                return true;
            }
            break;
        case Direction::NONE:
            break;
    }
    return false;
}

void CMovingObject::init(int spriteSize, CConfig *setup) {
    config = setup;
    src = {0, 0, 32, 32};
    obj = {0, 0, spriteSize, spriteSize}; // pacman position and size
    texture = getTexture();
}

void CMovingObject::drawPreparation(SDL_Renderer *renderer) {
    obj.x = position.x;
    obj.y = position.y;
    setModelToDraw(src);
    draw(renderer);
}