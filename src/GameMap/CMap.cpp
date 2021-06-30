#include "CMap.h"
#include "../Object/CMapObjects/CBonus.h"
#include "../Object/CMapObjects/CFood.h"
#include "../Object/CMapObjects/CEnergisers.h"
#include "../Object/CMapObjects/CEmpty.h"
#include "../Object/CMapObjects/CWall.h"

using namespace std;

bool CMap::loadMap(SDL_Renderer *renderer, CConfig *setup) {
    config = setup;
    if (!map.empty())
        quit();
    ifstream in("../alekhkir/examples/tile_positions.txt");
    if (!in.is_open()) {
        cout << "Unable to read map configs" << endl;
        in.close();
        return false;
    }

    width = config->mapWidth;
    height = config->mapHeight;

    if (!checkDimensionsConfig()) {
        if (!map.empty())
            quit();
        cout << "Map configuration sizes incorrect!" << endl;
        return false;
    }

    int tileType, teleportCount = 0;
    /* Initializing row of objects */
    vector<CObject*> tmpVector;
    /* Reading map with tile's positions from file */
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            /* Resetting flags for next tile */
            CTilePos tmpPos{config->tileSize * j, config->tileSize * i};
            in >> tileType;
            if (tileType != 0) {
                if (tileType == 40) { // teleport
                    CEmpty *empty = new CEmpty;
                    empty->setImage("../alekhkir/assets/tiles.png", renderer);
                    switch (teleportCount) {
                        case 0:
                            teleports.first = tmpPos;
                            break;
                        case 1:
                            teleports.second = tmpPos;
                            break;
                        default:
                            break;
                    }
                    teleportCount++;
                    tmpVector.push_back(empty);
                    continue;
                }
                if (tileType == 8) { // food
                    foodCount++;
                    CFood *food = new CFood;
                    food->setImage("../alekhkir/assets/tiles.png", renderer);
                    food->setSource((tileType - 1) * 32, 0, 32, 32);
                    food->setPosition(tmpPos, config->tileSize);
                    food->setId(tileType);
                    tmpVector.push_back(food);
                    continue;
                }
                if (tileType == 14) { // energiser
                    foodCount++;
                    CEnergisers *energiser = new CEnergisers;
                    energiser->setImage("../alekhkir/assets/tiles.png", renderer);
                    energiser->setSource((tileType - 1) * 32, 0, 32, 32);
                    energiser->setPosition(tmpPos, config->tileSize);
                    energiser->setId(tileType);
                    tmpVector.push_back(energiser);
                    continue;
                }
                CWall *wall = new CWall;
                wall->setImage("../alekhkir/assets/tiles.png", renderer);
                /* Finding needed sheet from tiles.png */
                wall->setSource((tileType - 1) * 32, 0, 32, 32);
                wall->setPosition(tmpPos, config->tileSize);
                wall->setId(tileType);
                /* Pushing object to current vector (line) */
                tmpVector.push_back(wall);
            } else {
                CEmpty *empty = new CEmpty;
                empty->setImage("../alekhkir/assets/tiles.png", renderer);
                empty->setSource(0, 0, 0, 0);
                empty->setPosition(tmpPos, config->tileSize);
                empty->setId(tileType);
                tmpVector.push_back(empty);
            }
        }
        /* Adding value to map line by line */
        map.push_back(tmpVector);
        tmpVector.clear();
    }

    if (teleportCount != 2) {
        cout << "Restricted number of teleports has been added!" << endl;
        return false;
    }
    in.close();
    return true;
}

void CMap::draw(SDL_Renderer *renderer, int bonusCount) {
    int mapSize = map.size();
    if (mapSize <= 0) {
        cout << "Map is empty" << endl;
        return;
    }
    int lineSize = map[0].size();
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < lineSize; j++) {
            /* Changing pos to draw and returning it back (solving shift for scoreboard) */
            CTilePos tmp {map[i][j]->getPosition().x, map[i][j]->getPosition().y};
            map[i][j]->setPosition({map[i][j]->getPosition().x, map[i][j]->getPosition().y + config->shift * config->tileSize}, config->tileSize);
            map[i][j]->draw(renderer);
            map[i][j]->setPosition(tmp, config->tileSize);
        }
    }
    drawFooter(renderer, bonusCount);
}

void CMap::generateBonus(int level, SDL_Renderer *renderer) {
    CBonus *bonus = new CBonus;
    bonus->setImage("../alekhkir/assets/tiles.png", renderer);
    bonus->setCanStep(true);
    bonus->setId(34); // declaring that it's bonus
    /* Select source depending on level (each level has different bonus) */
    switch (level % 3) {
        case 0:
            bonus->setSource(34 * 32, 0, 32, 32); // strawberry
            break;
        case 1:
            bonus->setSource(35 * 32, 0, 32, 32); // orange
            break;
        case 2:
            bonus->setSource(33 * 32, 0, 32, 32); // cherry
            break;
    }
    /* Place bonus randomly on a map */
    srand(time(nullptr)); // seeding random to get different position each time we start application
    int x = 0, y = 0;
    CTilePos currPos{x, y};
    while (!getTile(x, y).canStepOn() || getTile(x, y).getId() == 0
           || getTile(x, y).getId() == 14) {
        x = rand() % config->mapWidth - 1 + 1;
        y = rand() % config->mapHeight - 1 + 1;
        currPos = {x, y};
    }
    bonus->setPosition(currPos * config->tileSize, config->tileSize);
    getTile(currPos.x, currPos.y).quit();
    delete map[currPos.y][currPos.x];
    map[currPos.y].insert(map[currPos.y].begin() + currPos.x, bonus);
    map[currPos.y].erase(map[currPos.y].begin() + currPos.x + 1);
}

void CMap::drawFooter(SDL_Renderer *renderer, int bonusCount) {
    /* Pacman lives indicator */
    SDL_Surface *surface;
    SDL_Texture *texture;
    surface = IMG_Load("../alekhkir/assets/pacman_sheet.png");
    if (surface == nullptr)
        cout << "IMG_Load failure: " << IMG_GetError() << endl;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr)
        cout << "SDL_CreateTextureFromSurface failure: " << SDL_GetError() << endl;
    SDL_Rect footerPacmanSrc = {33, 0, 32, 32};
    for (int i = 1; i <= config->pacmanLives; i++) {
        SDL_Rect footerPacmanPos = {i * config->tileSize,
                                    config->mapHeight * config->tileSize - (config->tileSize / 2 * 3),
                                    config->tileSize, config->tileSize}; // pacman position and size
        SDL_RenderCopy(renderer, texture, &footerPacmanSrc, &footerPacmanPos);
    }
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    /* Cherry picture */
    surface = IMG_Load("../alekhkir/assets/tiles.png");
    if (surface == nullptr)
        cout << "IMG_Load failure: " << IMG_GetError() << endl;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr)
        cout << "SDL_CreateTextureFromSurface failure: " << SDL_GetError() << endl;
    SDL_Rect footerCherrySrc = {33 * 32, 0, 32, 32};
    SDL_Rect footerCherryPos = {config->mapWidth * config->tileSize - (4 * config->tileSize),
                                config->mapHeight * config->tileSize - (config->tileSize / 2 * 3),
                                config->tileSize, config->tileSize}; // cherry position and size
    SDL_RenderCopy(renderer, texture, &footerCherrySrc, &footerCherryPos);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    bonusCounter(renderer, bonusCount);
}

void CMap::bonusCounter(SDL_Renderer *renderer, int bonusCount) {
    /* Cherry (fruits) counter at the bottom */
    TTF_Font *counterFont = TTF_OpenFont("../alekhkir/assets/emulogic.ttf", 2 * config->height / config->mapHeight);
    ostringstream oss;
    oss << setw(2) << setfill('0') << bonusCount;
    SDL_Surface *bonusSurface = TTF_RenderUTF8_Blended(counterFont, oss.str().c_str(), {255, 255, 255, 0});
    SDL_Rect bonusRect = {0, 0, bonusSurface->w, bonusSurface->h};
    SDL_Texture *bonusTexture = SDL_CreateTextureFromSurface(renderer, bonusSurface);
    SDL_FreeSurface(bonusSurface);

    SDL_Rect DestScoreRect = bonusRect;
    DestScoreRect.x = config->mapWidth * config->tileSize - (3 * config->tileSize);
    DestScoreRect.y = config->mapHeight * config->tileSize - (config->tileSize / 2 * 3);
    SDL_RenderCopy(renderer, bonusTexture, &bonusRect, &DestScoreRect);
    SDL_DestroyTexture(bonusTexture);
    TTF_CloseFont(counterFont);
}

void CMap::quit() {
    int mapSize = map.size();
    int lineSize = map[0].size();
    for (int i = 0; i < mapSize; i++){
        for (int j = 0; j < lineSize; j++) {
            map[i][j]->quit();
            map[i][j]->setTexture(nullptr);
            delete map[i][j];
        }
        map[i].clear();
    }
    map.clear();
}

bool CMap::checkDimensionsConfig() {
    ifstream tmpIn("../alekhkir/examples/tile_positions.txt");
    int count = 0, tmp;
    while (!tmpIn.eof()){
        tmpIn >> tmp;
        count++;
    }
    tmpIn.close();
    return count == width * (height - config->shift - 1);
}