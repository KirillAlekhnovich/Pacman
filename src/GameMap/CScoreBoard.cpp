#include "CScoreBoard.h"

using namespace std;

bool CScoreBoard::init(CConfig *setup) {
    config = setup;
    if (TTF_Init() < 0) {
        cout << "TTF_INIT failure: " << SDL_GetError() << endl;
        return false;
    }
    gameFont = TTF_OpenFont("../alekhkir/assets/emulogic.ttf", 2 * config->height / config->mapHeight);
    return true;
}

void CScoreBoard::setScoreParameters(SDL_Renderer *renderer, int score, int highScore) {
    ostringstream oss, oss1;
    oss << "Score:" << setw(6) << setfill('0') << score;
    scoreSurface = TTF_RenderUTF8_Blended(gameFont, oss.str().c_str(), {255, 255, 255, 0});
    scoreRect = {0, 0, scoreSurface->w, scoreSurface->h};
    scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_FreeSurface(scoreSurface);

    oss1 << "HighScore:" << setw(6) << setfill('0') << highScore;
    highScoreSurface = TTF_RenderUTF8_Blended(gameFont, oss1.str().c_str(), {255, 255, 255, 0});
    highScoreRect = {0, 0, highScoreSurface->w, highScoreSurface->h};
    highScoreTexture = SDL_CreateTextureFromSurface(renderer, highScoreSurface);
    SDL_FreeSurface(highScoreSurface);
}

void CScoreBoard::quit() {
    TTF_CloseFont(gameFont);
}

void CScoreBoard::draw(SDL_Renderer *renderer) {
    SDL_Rect DestScoreRect = scoreRect;
    DestScoreRect.x = (config->mapWidth * config->tileSize - DestScoreRect.w) / 10;
    DestScoreRect.y = config->shift * config->tileSize / 2;
    SDL_RenderCopy(renderer, scoreTexture, &scoreRect, &DestScoreRect);

    SDL_Rect DestHighScoreRect = highScoreRect;
    DestHighScoreRect.x = (config->mapWidth * config->tileSize - DestHighScoreRect.w) / 10 * 9;
    DestHighScoreRect.y = config->shift * config->tileSize / 2;
    SDL_RenderCopy(renderer, highScoreTexture, &highScoreRect, &DestHighScoreRect);
    SDL_DestroyTexture(scoreTexture);
    SDL_DestroyTexture(highScoreTexture);
}