#pragma once
#include <iostream>
#include "../CObject.h"

/**
* @brief Energiser on a map
*/
class CEnergisers : public CObject {
public:
    /**
    * @brief Energiser constructor
    */
    CEnergisers() : CObject() {}
    /**
     * @brief Eating this object
     * @return Number of points that must be given to Pacman
     */
    int eat() const override { return 50; }
};
