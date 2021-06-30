#include "CPink.h"

using namespace std;

CTilePos CPink::calcDestination(const CTilePos &pacmanPos, Direction pacmanDir) {
    CTilePos tmp;
    switch (pacmanDir) { // pink's destination is a tile that is 4 tiles in front of Pacman
        case Direction::UP:
            tmp.x = pacmanPos.x;
            tmp.y = pacmanPos.y - 4;
            break;
        case Direction::DOWN:
            tmp.x = pacmanPos.x;
            tmp.y = pacmanPos.y + 4;
            break;
        case Direction::LEFT:
            tmp.x = pacmanPos.x - 4;
            tmp.y = pacmanPos.y;
            break;
        case Direction::RIGHT:
            tmp.x = pacmanPos.x + 4;
            tmp.y = pacmanPos.y;
            break;
        case Direction::NONE:
            break;
    }
    return tmp;
}