#pragma once
#include "../CObject.h"
#include <iostream>

/**
* @brief Bonus on the map
*/
class CBonus : public CObject {
public:
    /**
     * @brief Bonus constructor
     */
    CBonus() : CObject() {}
    /**
     * @brief Eating this object
     * @return Number of points that must be given to Pacman
     */
    int eat() const override { return 100; }
};
