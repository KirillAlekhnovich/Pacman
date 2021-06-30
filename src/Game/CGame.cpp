#include "CGame.h"

using namespace std;

bool CGame::input() {
    initSprites();
    bool canQuit = false;
    int startTicks = SDL_GetTicks();
    chaseStart = startTicks, roundStart = startTicks;
    highScore = config->highScore; // setting highScore as we have previously remembered
    scoreBoard.setScoreParameters(renderer, score, highScore);
    while (!canQuit) { // getting input
        SDL_RenderClear(renderer);
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                canQuit = true; // leaving loop if ctrl+c was pressed
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                    case SDLK_w:
                        pacman->setDirection(Direction::UP, map);
                        break;
                    case SDLK_DOWN:
                    case SDLK_s:
                        pacman->setDirection(Direction::DOWN, map);
                        break;
                    case SDLK_LEFT:
                    case SDLK_a:
                        pacman->setDirection(Direction::LEFT, map);
                        break;
                    case SDLK_RIGHT:
                    case SDLK_d:
                        pacman->setDirection(Direction::RIGHT, map);
                        break;
                    case SDLK_ESCAPE:
                        quit();
                        SDL_RenderSetScale(renderer, 1, 1);
                        return true;
                }
            }
        }
        update(); // drawing sprites
        modeTimers(); // check if we have to change mode
        if (gameMode == GameMode::CHASE) {
            for (size_t i = 0; i < ghosts.size(); i++)
                if (!ghosts[i]->isPrisoned())
                    ghosts[i]->setDestination(ghosts[i]->calcDestination(pacman->getPosition(),
                                                                         pacman->getCurrentDirection()));
        }

        eat(); // eating coins and energisers
        for (size_t i = 0; i < ghosts.size(); i++) {
            spritesCollision(ghosts[i]); // checking collision between Pacman and ghosts
            outOfPrison(ghosts[i], (int) (500 * i)); // if time is up let ghosts out
        }
        if (config->pacmanLives <= 0) {
            bonusCounter = 0;
            map.setFoodCount(0);
            map.setFoodCount(0);
            score = 0;
            frightenedEaten = 0;
            if (!gameOver()) {
                quit();
                restart = true;
                return true;
            }
            quit();
            if (config->width == 0 && config->height == 0) // quitting if ctrl+c was pressed, else open menu
                return false;
            return true;
        }
        /* Limiting FPS */
        int newTicks = SDL_GetTicks();
        if (1000 / 60 > newTicks - startTicks)
            SDL_Delay(1000 / 60 - (newTicks - startTicks));
        startTicks = newTicks;

        SDL_RenderSetScale(renderer, config->scale, config->scale);
        SDL_RenderPresent(renderer);
    }
    quit(); // program will reach this spot if only ctrl+c was pressed
    return false;
}

void CGame::quit() {
    for (size_t i = 0; i < ghosts.size(); i++) {
        ghosts[i]->quit(); // deleting each ghost's texture
        delete ghosts[i];
    }
    ghosts.clear();
    pacman->quit();
    delete pacman;
    map.quit();
    scoreBoard.quit();
}

bool CGame::run(CConfig *setup, SDL_Renderer *ren, SDL_Window *win) {
    window = win;
    renderer = ren;
    config = setup;
    gameMode = GameMode::CHASE;
    restart = false;
    SDL_RenderClear(renderer);
    if (!scoreBoard.init(config))
        return false;
    if (!map.loadMap(renderer, config))
        return false;
    SDL_UpdateWindowSurface(window);
    if (!input())
        return false;
    int tmpHighScore = highScore;
    config->setup(); // resetting configs for new game
    config->highScore = tmpHighScore; // remembering highScore
    return true;
}

void CGame::nextLvl() {
    frightenedEaten = 0;
    config->pacmanSpeed += 2;
    config->ghostsSpeed += 2;
    map.loadMap(renderer, config);
    pacman->setPosition({config->pacmanStartX * config->tileSize, config->pacmanStartY * config->tileSize},
                        (int) (config->tileSize * 1.25));
    pacman->setDirection(Direction::NONE, map);
    pacman->setSpeed(config->pacmanSpeed);
    for (size_t i = 0; i < ghosts.size(); i++)
        ghosts[i]->reset({config->redStartX, config->redStartY});

    level++;
    gameMode = GameMode::CHASE;
    roundStart = SDL_GetTicks(), chaseStart = SDL_GetTicks();
    srand(time(nullptr));
    if (rand() % 100 <= config->bonusSpawnChance) // placing bonuses depending on it's spawn chance
        map.generateBonus(level, renderer); // bonuses are generated starting with 2 level
}

void CGame::initSprites() {
    pacman = new CPacman;
    pacman->setSpeed(config->pacmanSpeed);
    pacman->setPosition({config->pacmanStartX * config->tileSize, config->pacmanStartY * config->tileSize},
                        config->tileSize);
    pacman->setImage("../alekhkir/assets/pacman_sheet.png", renderer);
    pacman->init((int) (config->tileSize * 1.25), config);

    CRed *red = new CRed;
    red->setDestination(pacman->getPosition());
    red->setStartingPos({config->redStartX, config->redStartY});
    red->setPosition(red->getStartingPos() * config->tileSize, config->tileSize);
    red->setImage("../alekhkir/assets/Red.png", renderer);
    ghosts.push_back(red);

    COrange *orange = new COrange;
    orange->setImage("../alekhkir/assets/Orange.png", renderer);
    ghosts.push_back(orange);

    CPink *pink = new CPink;
    pink->setImage("../alekhkir/assets/Pink.png", renderer);
    ghosts.push_back(pink);

    CBlue *blue = new CBlue(red);
    blue->setImage("../alekhkir/assets/Blue.png", renderer);
    ghosts.push_back(blue);

    for (size_t i = 0; i < ghosts.size(); i++) {
        if (i >= 1){ // for all ghosts except red set position in prison and destination to get out of it
            ghosts[i]->setDestination(red->getStartingPos() * config->tileSize);
            ghosts[i]->setStartingPos({(int) (config->redStartX - 2 + i), config->redStartY + 3});
            ghosts[i]->setPosition(ghosts[i]->getStartingPos() * config->tileSize, config->tileSize);
        }
        ghosts[i]->setSpeed(config->ghostsSpeed);
        ghosts[i]->init((int) (config->tileSize * 1.25), config);
        ghosts[i]->setDirection(Direction::UP, map);
    }
}

bool CGame::gameOver() const{
    CGameOverMenu gameOverMenu;
    CObject tmp;
    SDL_Surface *surface;
    SDL_Texture *texture;
    surface = IMG_Load("../alekhkir/assets/game_over.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    tmp.setSource(0, 0, 288, 32);
    SDL_Rect dest = {0, config->mapHeight * config->tileSize / 5 * 3,
                     config->width - config->width / 5, (config->width - config->width / 5) / 9};
    dest.x = (config->mapWidth * config->tileSize - dest.w) / 2;
    SDL_Rect src = tmp.getSource();
    SDL_RenderCopy(renderer, texture, &src, &dest);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
    SDL_Delay(2000);
    config->highScore = highScore; // remembering highScore if game is over

    SDL_RenderSetScale(renderer, 1, 1);
    return !gameOverMenu.call(window, renderer, config);
}

void CGame::modeTimers() {
    if ((int) SDL_GetTicks() - frightenedStart >= config->frightenedTime && gameMode == GameMode::FRIGHTENED) {
        gameMode = GameMode::CHASE;
        frightenedEaten = 0; // resetting number of eaten ghosts in current mode
        for (size_t i = 0; i < ghosts.size(); i++) {
            ghosts[i]->setSpeed(config->ghostsSpeed);
            if (!ghosts[i]->isPrisoned())
                ghosts[i]->setDestination(ghosts[i]->calcDestination(pacman->getPosition(),
                                                                     pacman->getCurrentDirection()));
            else
                ghosts[i]->setPrisonedTimer(SDL_GetTicks());
        }
        chaseStart = SDL_GetTicks(); // timing mode
    }

    if ((int) SDL_GetTicks() - chaseStart >= config->chaseTime && gameMode == GameMode::CHASE) {
        gameMode = GameMode::SCATTER;
        scatterStart = SDL_GetTicks();
        for (size_t i = 0; i < ghosts.size(); i++)
            if (!ghosts[i]->isPrisoned())
                ghosts[i]->setDestination({0, 0}); // in scatter mode all ghosts go to the up-left corner
    }

    if ((int) SDL_GetTicks() - scatterStart >= config->scatterTime && gameMode == GameMode::SCATTER) {
        gameMode = GameMode::CHASE;
        chaseStart = SDL_GetTicks();
        for (size_t i = 0; i < ghosts.size(); i++)
            if (!ghosts[i]->isPrisoned())
                ghosts[i]->setDestination(ghosts[i]->calcDestination(pacman->getPosition(),
                                                                     pacman->getCurrentDirection()));
    }
}

void CGame::update() {
    map.draw(renderer, bonusCounter);
    pacman->move(renderer, map);
    pacman->drawPreparation(renderer);

    for (size_t i = 0; i < ghosts.size(); i++) {
        if (pacman->getCurrentDirection() != Direction::NONE && (int) (SDL_GetTicks() - roundStart) >  (int) (2000 * (i + 1))) {
            if (ghosts[i]->isPrisoned() && ghosts[i]->getPosition().y < (config->redStartY + 2) * config->tileSize)
                ghosts[i]->setInGates(true); // avoiding ghosts stuck at the gates while mode has been changed
            if (!(ghosts[i]->isPrisoned() && gameMode == GameMode::FRIGHTENED) || ghosts[i]->isInGates())
                ghosts[i]->move(renderer, map); // move ghost if it's not in prison
        }
        ghosts[i]->setGameMode(&gameMode);
        ghosts[i]->drawPreparation(renderer);
    }
}

void CGame::eat() {
    /* Calling eat if we are at the beginning of the tile */
    if (pacman->getPosition().x % config->tileSize == 0 && pacman->getPosition().y % config->tileSize == 0) {
        int addition = pacman->foodCollision(map);
        if (addition == 50) { // eating energiser
            gameMode = GameMode::FRIGHTENED;
            frightenedStart = SDL_GetTicks(); // timing beginning of frightened mode
            for (size_t i = 0; i < ghosts.size(); i++) {
                ghosts[i]->setSpeed(config->ghostsSpeed / 2); // reducing ghosts speed in frightened mode
                ghosts[i]->setFrightenedTimer(frightenedStart);
                srand(time(nullptr));
                if (!ghosts[i]->isPrisoned()) // sending ghosts to random location
                    ghosts[i]->setDestination({rand() % config->width, rand() % config->height});
            }
        }
        if (addition == 100) // fruit has been eaten
            bonusCounter++;
        score += addition; // incrementing score by function value
        if (highScore < score)
            highScore = score;
    }
    scoreBoard.setScoreParameters(renderer, score, highScore);
    scoreBoard.draw(renderer);
    if (map.getFoodCount() <= 0)
        nextLvl();
}

void CGame::spritesCollision(CGhost *ghost){
    /* Checking collision with corrected action box */
    if ((pacman->getPosition().x == ghost->getPosition().x
         && abs(pacman->getPosition().y - ghost->getPosition().y) < config->tileSize / 2)
        || (pacman->getPosition().y == ghost->getPosition().y
            && abs(pacman->getPosition().x - ghost->getPosition().x) < config->tileSize / 2)) {
        if (gameMode == GameMode::FRIGHTENED)
            ghostEaten(ghost);
        else {
            pacmanEaten();
            roundStart = SDL_GetTicks();
            chaseStart = roundStart;
        }
    }
}

void CGame::ghostEaten(CGhost *ghost) {
    ghost->setPosition({(config->redStartX - 1 + frightenedEaten) * config->tileSize,
                        (config->redStartY + 3) * config->tileSize},
                       (int) (config->tileSize * 1.25));
    frightenedEaten++;
    score += frightenedEaten * 200; // increasing score added if more than one ghost was eaten
    ghost->setPrisoned(true);
    ghost->setDestination({config->redStartX * config->tileSize, config->redStartY * config->tileSize});
    ghost->setDirection(Direction::NONE, map);
}

void CGame::pacmanEaten() const{
    config->pacmanLives--;
    pacman->setPosition({config->pacmanStartX * config->tileSize,
                         config->pacmanStartY * config->tileSize}, (int) (config->tileSize * 1.25));
    for (size_t i = 0; i < ghosts.size(); i++)
        ghosts[i]->reset({config->redStartX, config->redStartY});
    SDL_Delay(1000);
}

void CGame::outOfPrison(CGhost *ghost, int additionalWait) {
    if ((((int) SDL_GetTicks() + additionalWait - ghost->getPrisonedTimer()) >= config->detentionTime) &&
        ghost->getPrisonedTimer() != 0 && ghost->isPrisoned()) {
        ghost->setDirection(Direction::UP, map);
        ghost->setPrisonedTimer(0);
    }
}