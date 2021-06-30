#pragma once
#include "CGhost.h"

/**
* @brief Pink ghost
*/
class CPink : public CGhost{
public:
    /**
     * @brief Constructor for pink ghost
     */
    CPink() : CGhost(true) {}
    /**
      * @brief Calculation target for pink ghost
      * @param pacmanPos Pacman position
      * @param pacmanDir Pacman direction
      * @return Returning pink's destination
      */
    CTilePos calcDestination(const CTilePos &pacmanPos, Direction pacmanDir) override;
};
