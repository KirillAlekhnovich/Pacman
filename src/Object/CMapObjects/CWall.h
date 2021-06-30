#pragma once
#include <iostream>
#include "../CObject.h"

/**
* @brief Walls on a map
*/
class CWall : public CObject {
public:
    /**
    * @brief Wall constructor
    */
    CWall() : CObject(false) {}
};
