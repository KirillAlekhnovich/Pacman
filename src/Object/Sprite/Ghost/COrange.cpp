#include "COrange.h"

using namespace std;

void COrange::scaredDetection(CTilePos pacmanPos) {
    if (calculateHypotenuse(position / config->tileSize,
                                    pacmanPos / config->tileSize) < 8 * 8 && !scared)
        scared = true; // if orange is 8 or less tiles close to pacman
    else if (calculateHypotenuse(position / config->tileSize,
                                         pacmanPos / config->tileSize) > 8 * 8 && scared)
        scared = false;
}

CTilePos COrange::calcDestination(const CTilePos &pacmanPos, Direction pacmanDir) {
    scaredDetection(pacmanPos);
    if (scared)
        return CTilePos{0, config->mapHeight * config->tileSize};
    else
        return pacmanPos;
}