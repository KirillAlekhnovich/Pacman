#pragma once
#include "CGhost.h"
#include "CRed.h"

/**
* @file CBlue.h
* @brief Blue ghost
*/
class CBlue : public CGhost{
public:
    /**
     * @brief Constructor for blue ghost
     */
    CBlue(CRed *mRed) : CGhost(true), red(mRed) {}
    /**
     * @brief Calculation target for blue ghost
     * @param pacmanPos Pacman position
     * @param pacmanDir Pacman direction
     * @return Returning blue's destination
     */
    CTilePos calcDestination(const CTilePos &pacmanPos, Direction pacmanDir) override;
private:
    CRed *red{}; // Blue ghost should have pointer to red one to calculate it's destination
};