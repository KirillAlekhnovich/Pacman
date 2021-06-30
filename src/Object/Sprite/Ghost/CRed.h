#pragma once
#include "CGhost.h"

/**
* @brief Red ghost
*/
class CRed : public CGhost{
public:
    /**
     * @brief Constructor for red ghost
     */
    CRed() : CGhost(false) {}
    /**
     * @brief Resetting red's position and speed
     * @param target Red's target
     */
    void reset(CTilePos target) override;
    /**
      * @brief Calculation target for red ghost
      * @param pacmanPos Pacman position
      * @param pacmanDir Pacman direction
      * @return Returning red's destination
      */
    CTilePos calcDestination(const CTilePos &pacmanPos, Direction pacmanDir) override;
};
