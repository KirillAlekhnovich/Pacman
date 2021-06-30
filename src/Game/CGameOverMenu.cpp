#include "CGameOverMenu.h"

void CGameOverMenu::prepareTextures() {
    menuFont = TTF_OpenFont("../alekhkir/assets/emulogic.ttf", config->width / 15);
    SDL_Surface* TextSurface;

    TextSurface = TTF_RenderUTF8_Blended(menuFont, "Play again?", {255, 255, 255, 0});
    playAgain = {0, 0, TextSurface->w, TextSurface->h};
    playAgainTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);
    SDL_FreeSurface(TextSurface);

    TextSurface = TTF_RenderUTF8_Blended(menuFont, "Yes", {255, 255, 255, 0});
    voteYes = {0, 0, TextSurface->w, TextSurface->h};
    voteYesTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);
    SDL_FreeSurface(TextSurface);

    TextSurface = TTF_RenderUTF8_Blended(menuFont, "No", {255, 255, 255, 0});
    voteNo = {0, 0, TextSurface->w, TextSurface->h};
    voteNoTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);
    SDL_FreeSurface(TextSurface);
}

bool CGameOverMenu::call(SDL_Window *win, SDL_Renderer *ren, CConfig *setup) {
    window = win;
    renderer = ren;
    config = setup;
    CGame game;
    prepareTextures();
    int tmpHighScore = config->highScore;
    if (input()){
        config->setup(); // resetting configs for new game
        config->highScore = tmpHighScore; // remembering highScore
        quit();
        return true;
    }
    quit();
    return false;
}

void CGameOverMenu::render() const {
    SDL_RenderClear(renderer);

    {
        SDL_Rect DestOptionsRect = playAgain;
        DestOptionsRect.x = (config->width - DestOptionsRect.w) / 2;
        DestOptionsRect.y = config->height / 2 - config->height / 3;
        SDL_RenderCopy(renderer, playAgainTexture, &playAgain, &DestOptionsRect);
    }

    /* Creating vector of options (so we can easily add more) */
    vector<int> optionPositions {config->height / 2, config->height / 2 + config->height / 5};

    {
        SDL_Rect DestOptionsRect = voteYes;
        DestOptionsRect.x = (config->width - DestOptionsRect.w) / 2;
        DestOptionsRect.y = optionPositions[0];
        SDL_RenderCopy(renderer, voteYesTexture, &voteYes, &DestOptionsRect);
    }

    {
        SDL_Rect DestOptionsRect = voteNo;
        DestOptionsRect.x = (config->width - DestOptionsRect.w) / 2;
        DestOptionsRect.y = optionPositions[1];
        SDL_RenderCopy(renderer, voteNoTexture, &voteNo, &DestOptionsRect);
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

bool CGameOverMenu::input() {
    bool canQuit = false;
    while (!canQuit){
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                canQuit = true;
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
                                return true;
                            case 1:
                                return false;
                        }
                        break;
                    case SDLK_ESCAPE:
                        return false;
                }
            }
        }
        render(); // drawing
    }
    /* Setting width and height as 0 to determine that ctrl+c was pressed */
    config->width = 0;
    config->height = 0;
    return false;
}

void CGameOverMenu::quit() {
    SDL_DestroyTexture(playAgainTexture);
    playAgainTexture = nullptr;
    SDL_DestroyTexture(voteNoTexture);
    voteNoTexture = nullptr;
    SDL_DestroyTexture(voteYesTexture);
    voteYesTexture = nullptr;
    TTF_CloseFont(menuFont);
}