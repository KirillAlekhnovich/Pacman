#pragma once
#include <iostream>
#include "../CObject.h"

/**
* @brief Food on a map
*/
class CFood : public CObject {
public:
    /**
    * @brief Food constructor
    */
    CFood() : CObject() {}
    /**
     * @brief Eating this object
     * @return Number of points that must be given to Pacman
     */
    int eat() const override { return 10; }
};
