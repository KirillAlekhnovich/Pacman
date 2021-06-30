#pragma once

#include "Sprite/Direction.h"

using namespace std;

/**
* @brief Class for working with position
*/
class CTilePos {
public:
    /**
     * @brief Constructor for position
     * @param x Dimension x
     * @param y Dimension y
     */
    CTilePos(int x = 0, int y = 0) : x(x), y(y) {}
    /**
     * @brief Moving an object
     * @param direction Current object's direction
     * @param speed Object's speed
     * @return New object's position
     */
    CTilePos move(Direction &direction, int speed) {
        CTilePos tmp;
        tmp.x = x;
        tmp.y = y;
        for (int i = 0; i < speed; i++) {
            switch (direction) {
                case Direction::UP:
                    tmp.y -= 1;
                    break;
                case Direction::DOWN:
                    tmp.y += 1;
                    break;
                case Direction::LEFT:
                    tmp.x -= 1;
                    break;
                case Direction::RIGHT:
                    tmp.x += 1;
                    break;
                default:
                    break;
            }
        }
        return tmp;
    }
    /**
     * @brief Check if directions are opposite or not
     * @param dir1 First direction
     * @param dir2 Second direction
     * @return Boolean variable, that shows if directions are opposite or not
     */
    bool oppositeDirection(Direction &dir1, Direction &dir2) const {
        if ((dir1 == Direction::UP && dir2 == Direction::DOWN)
            || (dir1 == Direction::DOWN && dir2 == Direction::UP))
            return true;
        if ((dir1 == Direction::LEFT && dir2 == Direction::RIGHT)
            || (dir1 == Direction::RIGHT && dir2 == Direction::LEFT))
            return true;
        return false;
    }
    /**
     * @brief Operator ==
     * @param rhs Right side
     * @return Position's equality
     */
    bool operator==(const CTilePos &rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    /**
     * @brief Operator !=
     * @param rhs Right side
     * @return Positions inequality
     */
    bool operator!=(const CTilePos &rhs) const {
        return !(rhs == *this);
    }
    /**
     * @brief Operator *
     * @param index Position multiplier
     * @return New position
     */
    CTilePos operator*(int index) const {
        CTilePos tmp;
        tmp.x = x * index;
        tmp.y = y * index;
        return tmp;
    }
    /**
     * @brief Operator +
     * @param index Number that has to be added to position dimensions
     * @return New position
     */
    CTilePos operator+(int index) const {
        CTilePos tmp;
        tmp.x = x + index;
        tmp.y = y + index;
        return tmp;
    }
    /**
     * @brief Operator =
     * @param newPosition New position
     * @return Assigned position
     */
    CTilePos &operator=(CTilePos newPosition) {
        x = newPosition.x;
        y = newPosition.y;
        return *this;
    }
    /**
     * @brief Operator /
     * @param index Divider
     * @return New position
     */
    CTilePos operator/(int index) const {
        CTilePos tmp;
        tmp.x = x / index;
        tmp.y = y / index;
        return tmp;
    }

    int x;
    int y;
};
