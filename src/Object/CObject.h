#pragma once
#include <vector>
#include "CTilePos.h"
#include "../Game/CConfig.h"
#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

/**
* @brief General class for all objects
*/
class CObject {
public:
    /**
     * @brief Object's empty constructor
     */
    CObject() : canStep(true) {}
    /**
     * @brief Constructor with canStep parameter
     * @param c CanStep
     */
    explicit CObject(bool c) : canStep(c) {}
    /**
    * @brief Virtual destructor
    */
    virtual ~CObject()= default;
    /**
     * @brief Setting position
     * @param pos New position
     * @param tileSize Object's size
     */
    void setPosition(const CTilePos &pos, int tileSize);
    /**
     * @brief Setting source rectangle
     * @param x Dimension x
     * @param y Dimension y
     * @param w Width
     * @param h Height
     */
    void setSource(int x, int y, int w, int h);
    /**
     * @brief Setting image to an object
     * @param filename Name of a file from which we are importing image
     * @param renderer App's renderer
     */
    void setImage(const string& filename, SDL_Renderer *renderer);
    /**
     * @brief Drawing current object
     * @param renderer App's renderer
     */
    void draw(SDL_Renderer *renderer) const;
    /**
     * @brief Deleting object's texture
     */
    void quit() const;
    /**
     * @brief Setting that you can step on a tile
     * @param s Can step boolean
     */
    void setCanStep(bool s) { canStep = s; }
    /**
     * @brief Setting object's id
     * @param i Id
     */
    void setId(int i) { id = i; }
    /**
     * @brief Setting object's texture
     * @param tex Texture
     */
    void setTexture(SDL_Texture *tex) { texture = tex; }
    /**
     * @brief Getting object's source
     * @return Source rectangle
     */
    SDL_Rect getSource() const { return src; }
    /**
     * @brief Getting object's texture
     * @return Texture
     */
    SDL_Texture *getTexture() const { return texture; }
    /**
     * @brief Can step getter
     * @return Boolean that shows if sprite can step on this tile
     */
    bool canStepOn() const { return canStep; }
    /**
     * @brief Getting object's id
     * @return Object's id
     */
    int getId() const { return id; }
    /**
     * @brief Getting object's position
     * @return Object's position
     */
    const CTilePos &getPosition() const;
    /**
     * @brief Eating this tile method
     * @return Points that must be given to Pacman
     */
    virtual int eat() const;
protected:
    CConfig *config{};
    int id{};
    CTilePos position{0, 0};
    bool canStep;
    SDL_Texture *texture{};
    SDL_Rect obj{};
    SDL_Rect src{};
};
