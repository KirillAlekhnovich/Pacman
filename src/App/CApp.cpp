#include "CApp.h"
#include "../Game/CMainMenu.h"
#include <iostream>

using namespace std;

bool CApp::init() {
    if (!config.setup())
        return false;

    /* Initializing SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "STD_INIT failure: " << SDL_GetError() << endl;
        return false;
    }

    /* Initializing IMG */
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        cout << "IMG_INIT failure: " << SDL_GetError() << endl;
        return false;
    }

    /* Creating window */
    window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              config.width, config.height, 0);
    if (window == nullptr) {
        cout << "SDL_CreateWindow failure: " << SDL_GetError() << endl;
        return false;
    }

    /* Creating renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        cout << "SDL_CreateRenderer failure: " << SDL_GetError() << endl;
        return false;
    }

    if (TTF_Init() < 0) {
        cout << "TTF_INIT failure: " << SDL_GetError() << endl;
        return false;
    }
    while (true){ // get back to menu until player will exit in menu or press ctrl+c
        if (menu.start(window, renderer, &config))
            continue;
        quit();
        return true;
    }
}

void CApp::quit() {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}