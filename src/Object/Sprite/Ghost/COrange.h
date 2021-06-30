#pragma once
#include "CGhost.h"

/**
* @brief Orange ghost
*/
class COrange : public CGhost{
public:
    /**
     * @brief Constructor for orange ghost
     */
    COrange() : CGhost(true) {}
    /**
     * @brief Setting if orange should be scared or not
     * @param pacmanPos Pacman position
     */
    void scaredDetection(CTilePos pacmanPos);
    /**
      * @brief Calculation target for orange ghost
      * @param pacmanPos Pacman position
      * @param pacmanDir Pacman direction
      * @return Returning orange's destination
      */
    CTilePos calcDestination(const CTilePos &pacmanPos, Direction pacmanDir) override;
    /**
     * @brief Setting scared boolean
     * @param s Scared
     */
    void setScared(bool s)  { scared = s; }
    /**
     * @brief Getting scared boolean
     * @return Scared or not
     */
    bool isScared() const { return scared; }
private:
    bool scared = false;
};
