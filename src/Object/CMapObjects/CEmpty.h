#pragma once
#include <iostream>
#include "../CObject.h"

/**
* @brief Empty object on a map
*/
class CEmpty : public CObject {
public:
    /**
    * @brief Empty tile constructor
    */
    CEmpty() : CObject() {}
};
