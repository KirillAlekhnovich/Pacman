#pragma once

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <iomanip>
#include <SDL2/SDL_ttf.h>
#include "../Game/CConfig.h"

/**
* @brief Score & high score counters
*/
class CScoreBoard {
public:
    /**
     * @brief Initializing font for scoreboard
     * @param setup Game's configurations
     * @return Boolean success variable
     */
    bool init(CConfig *setup);
    /**
     * @brief Setting score numbers
     * @param renderer App's renderer
     * @param score Current score
     * @param highScore Current high score
     */
    void setScoreParameters(SDL_Renderer *renderer, int score, int highScore);
    /**
     * @brief Closing font
     */
    void quit();
    /**
     * @brief Drawing scoreboard
     * @param renderer App's renderer
     */
    void draw(SDL_Renderer *renderer);
private:
    CConfig *config;
    TTF_Font * gameFont;
    SDL_Surface * scoreSurface;
    SDL_Rect scoreRect;
    SDL_Texture * scoreTexture;
    SDL_Surface * highScoreSurface;
    SDL_Rect highScoreRect;
    SDL_Texture * highScoreTexture;
};
