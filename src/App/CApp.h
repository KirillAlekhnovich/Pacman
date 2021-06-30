#pragma once

#include "../Game/CConfig.h"
#include "../Game/CMainMenu.h"
#include <SDL2/SDL.h>

/**
 * @brief Starting application
 */
class CApp {
public:
    /**
     * @brief Initializing window, renderer and font for the game.
     */
    bool init();
    /**
     * @brief Quitting sdl, image and ttf
     */
    void quit();
private:
    /**
     * @brief Game configurations.
     */
    CConfig config;
    /**
     * @brief Main menu.
     */
    CMainMenu menu;
    /**
     * @brief Game window.
     */
    SDL_Window * window;
    /**
     * @brief Game renderer.
     */
    SDL_Renderer * renderer;
};
