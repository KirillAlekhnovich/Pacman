#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "CConfig.h"
#include "CGame.h"
#include <iostream>

/**
* @brief Menu at the start of the game
*/
class CMainMenu {
public:
    /**
     * @brief Drawing menu
     */
    void render() const;
    /**
     * @brief Creating blocks (logo and options)
     * @return Returning false if something went wrong
     */
    bool createBlocks();
    /**
     * @brief Initializing main menu
     * @param win App's window
     * @param ren App's renderer
     * @param setup Game's configurations
     * @return Returning false if something went wrong
     */
    bool start(SDL_Window *win, SDL_Renderer *ren, CConfig *setup);
    /**
     * @brief Processing players input
     * @return Returning players choice
     */
    bool input();
    /**
     * @brief Destroying all the textures that has been used in this class
     */
    void destroyTextures() const;
private:
    CConfig * config{};
    SDL_Window * window{};
    SDL_Renderer * renderer{};
    SDL_Texture * logoPacmanTexture{};
    SDL_Texture * StartGameTexture{};
    SDL_Rect StartGameRect{};
    SDL_Texture * ExitTexture{};
    SDL_Rect ExitRect{};
    TTF_Font * gameFont{};
    int currentChoice = 0, maxChoices = 2;
};
