#include "CBlue.h"

using namespace std;

CTilePos CBlue::calcDestination(const CTilePos &pacmanPos, Direction pacmanDir) {
    CTilePos tmp;
    /* Blue's destination depends on Pacman's and Blinky's position */
    tmp.x = red->getPosition().x + 2 * (pacmanPos.x - red->getPosition().x);
    tmp.y = red->getPosition().y + 2 * (pacmanPos.y - red->getPosition().y);
    return tmp;
}