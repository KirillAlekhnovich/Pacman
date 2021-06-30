#include "CRed.h"

using namespace std;

CTilePos CRed::calcDestination(const CTilePos &pacmanPos, Direction pacmanDir) {
    return pacmanPos;
}

void CRed::reset(CTilePos target) {
    speed = config->ghostsSpeed;
    position = target * config->tileSize;
    currentDirection = Direction::LEFT;
}