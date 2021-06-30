#include "CConfig.h"
#include "../GameMap/CMap.h"

using namespace std;

bool CConfig::setup() {
    ifstream in("../alekhkir/examples/setup.txt");
    if (!in.is_open() || in.bad() || in.eof()) {
        cout << "Failed to load configurations." << endl;
        return false;
    }

    in >> width;
    in >> height;
    in >> ghostsSpeed;
    in >> pacmanSpeed;
    in >> pacmanLives;
    in >> mapWidth;
    in >> mapHeight;
    in >> pacmanStartX;
    in >> pacmanStartY;
    in >> shift;

    in >> chaseTime;
    in >> frightenedTime;
    in >> scatterTime;
    in >> detentionTime;
    in >> redStartX;
    in >> redStartY;
    in >> bonusSpawnChance;

    if (!check())
        return false;

    pacmanStartY += shift; // shifting to leave some place to scoreboard
    if (width <= height)
        /* Dividing actual width by max possible width */
        scale = (float) width / (float) (mapWidth * tileSize);
    else
        /* Dividing actual height by max possible height */
        scale = (float) height / (float) (mapHeight * tileSize);
    return true;
}

bool CConfig::check() const {
    ifstream tmpIn("../alekhkir/examples/setup.txt");
    int count = 0, tmp;
    while (!tmpIn.eof()){
        tmpIn >> tmp;
        count++;
    }
    tmpIn.close();
    if (count < 17) {
        cout << "Not enough configuration parameters!" << endl;
        return false;
    }
    if (width < 300 || height < 400 || mapHeight <= 0 || mapWidth <= 0) {
        cout << "Config dimensions error." << endl;
        return false;
    }
    if (tileSize <= 0 || shift < 3) {
        cout << "Unacceptable shift config." << endl;
        return false;
    }
    if (ghostsSpeed <= 0 || pacmanSpeed <= 0 || ghostsSpeed >= tileSize || pacmanSpeed >= tileSize) {
        cout << "Sprites speed is incorrect." << endl;
        return false;
    }
    if (pacmanStartX > mapWidth || pacmanStartY > mapHeight || pacmanStartX <= 0 || pacmanStartY <= 0) {
        cout << "Pacman start position is incorrect." << endl;
        return false;
    }
    if (redStartX > mapWidth || redStartY > mapHeight || redStartX <= 0 || redStartY <= 0) {
        cout << "Red start position is incorrect." << endl;
        return false;
    }
    if ((chaseTime <= 500 || detentionTime <= 500 || frightenedTime <= 500 || scatterTime <= 500)
        || (chaseTime >= 15000 || detentionTime >= 15000 || frightenedTime >= 15000 || scatterTime >= 15000)) {
        cout << "Timer configurations failed." << endl;
        return false;
    }
    if (bonusSpawnChance < 0 || bonusSpawnChance > 100) {
        cout << "Bonus spawn chance config error." << endl;
        return false;
    }
    return true;
}