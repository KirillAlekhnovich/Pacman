#include "CMainMenu.h"

using namespace std;

void CMainMenu::render() const{
    SDL_RenderClear(renderer);
    /* Setting place to draw a logo */
    SDL_Rect logoRect = {0, 0, config->height / 3 * 2, config->height / 3};
    logoRect.x = (config->width - logoRect.w) / 2;
    SDL_Rect logoSrc = {0, 0, 2700, 1350};
    SDL_RenderCopy(renderer, logoPacmanTexture, &logoSrc, &logoRect);

    /* Creating vector of options (so we can easily add more) */
    vector<int> optionPositions {config->height / 2, config->height / 2 + config->height / 5};

    {
        SDL_Rect DestOptionsRect = StartGameRect;
        DestOptionsRect.x = (config->width - DestOptionsRect.w) / 2;
        DestOptionsRect.y = optionPositions[0];
        SDL_RenderCopy(renderer, StartGameTexture, &StartGameRect, &DestOptionsRect);
    }

    {
        SDL_Rect DestOptionsRect = ExitRect;
        DestOptionsRect.x = (config->width - DestOptionsRect.w) / 2;
        DestOptionsRect.y = optionPositions[1];
        SDL_RenderCopy(renderer, ExitTexture, &ExitRect, &DestOptionsRect);
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_Rect ChoiceRect = {0, 0, 20, 20};
    /* Setting pos depending on configs (windows size) */
    ChoiceRect.x = (config->width - ChoiceRect.w) / 2 - config->width / 25 * 10;
    ChoiceRect.y = optionPositions[currentChoice] + config->width / 30; // shift it 1/2 of font size
    SDL_RenderFillRect(renderer, &ChoiceRect);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderPresent(renderer);
}

bool CMainMenu::input() {
    CGame game;
    bool canQuit = false;
    while (!canQuit){
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                canQuit = true; // ctrl+c handler
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        --currentChoice;
                        if (currentChoice < 0)
                            currentChoice = maxChoices - 1;
                        break;
                    case SDLK_DOWN:
                        ++currentChoice;
                        if (currentChoice >= maxChoices)
                            currentChoice = 0;
                        break;
                    case SDLK_RETURN:
                        switch (currentChoice) {
                            case 0:
                                destroyTextures();
                                while (true){ // if player wants to play once again - start a new game
                                    if (!game.run(config, renderer, window))
                                        return false;
                                    if (game.isRestart())
                                        continue;
                                    return true;
                                }
                            case 1:
                                destroyTextures();
                                return false;
                        }
                        break;
                    case SDLK_ESCAPE:
                        destroyTextures();
                        return false;
                }
            }
        }
        render();
    }
    destroyTextures();
    return false;
}


bool CMainMenu::start(SDL_Window *win, SDL_Renderer *ren, CConfig *setup) {
    window = win;
    renderer = ren;
    config = setup;
    if (!createBlocks())
        return false;
    return input();
}

bool CMainMenu::createBlocks() {
    SDL_Surface *logoPacmanSurface;
    logoPacmanSurface = IMG_Load("../alekhkir/assets/logo.png");
    if (logoPacmanSurface == nullptr) {
        cout << "IMG_Load failure: " << IMG_GetError() << endl;
        return false;
    }
    /* Creating texture from surface */
    logoPacmanTexture = SDL_CreateTextureFromSurface(renderer, logoPacmanSurface);
    SDL_FreeSurface(logoPacmanSurface);

    gameFont = TTF_OpenFont("../alekhkir/assets/emulogic.ttf", config->width / 15);

    /* Creating options */
    SDL_Surface* TextSurface;
    TextSurface = TTF_RenderUTF8_Blended(gameFont, "Start game", {255, 255, 255, 0});
    StartGameRect = {0, 0, TextSurface->w, TextSurface->h};
    StartGameTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);
    SDL_FreeSurface(TextSurface);

    TextSurface = TTF_RenderUTF8_Blended(gameFont, "Exit", {255, 255, 255, 0});
    ExitRect = {0, 0, TextSurface->w, TextSurface->h};
    ExitTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);
    SDL_FreeSurface(TextSurface);
    return true;
}

void CMainMenu::destroyTextures() const{
    SDL_DestroyTexture(StartGameTexture);
    SDL_DestroyTexture(ExitTexture);
    SDL_DestroyTexture(logoPacmanTexture);
    TTF_CloseFont(gameFont);
}