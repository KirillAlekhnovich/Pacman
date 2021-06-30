#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "CConfig.h"
#include "CGame.h"

/**
* @brief  Menu that is shown when Pamcan dies
*/
class CGameOverMenu {
public:
    /**
     * @brief Preparing textures for game over menu (texts)
     */
    void prepareTextures();
    /**
     * @brief Calling game over menu
     * @param win App's window
     * @param ren App's renderer
     * @param setup Game's configurations
     * @return True if player wants to play more, else - false
     */
    bool call(SDL_Window *win, SDL_Renderer *ren, CConfig *setup);
    /**
     * @brief Drawing menu
     */
    void render() const;
    /**
     * @brief Processing player's input
     * @return Returning boolean depending on player's choice
     */
    bool input();
    /**
     * @brief Destroying used textures and fonts
     */
    void quit();
private:
    CConfig * config{};
    SDL_Window * window{};
    SDL_Renderer * renderer{};
    SDL_Texture * playAgainTexture{};
    SDL_Rect playAgain{};
    SDL_Texture * voteYesTexture{};
    SDL_Rect voteYes{};
    SDL_Texture * voteNoTexture{};
    SDL_Rect voteNo{};
    TTF_Font * menuFont{};
    int currentChoice = 0, maxChoices = 2;
};
