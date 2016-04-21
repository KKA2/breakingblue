// Levels.cpp
// Implementation of Levels class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Levels.h"
#include "Texture.h"
#include "Level1.h"

using namespace std;

Levels::Levels() {
    CurrLevel = 0;
}

Levels::~Levels() {}

void Levels::setUp(SDL_Window *window, SDL_Renderer *renderer) {
    level1.setUp(window,renderer);
}

void Levels::loadMedia() {
    level1.loadMedia();
}

void Levels::display() {
    if (CurrLevel == 1)
        level1.display();
}

void Levels::playMusic() {
    if (CurrLevel == 1)
        level1.playMusic();
}

int Levels::getCurrLevel() {
    return CurrLevel;
}

void Levels::setCurrLevel(int currLevel) {
    CurrLevel = currLevel;
}

void Levels::setCameraX(int x) {
    if (CurrLevel == 1)
        level1.setCameraX(x);
}

int Levels::getCameraX() {
    if (CurrLevel == 1)
        return level1.getCameraX();
    else //not in a level!
        return 1;
}

SDL_Rect * Levels::getCamera() {
    if (CurrLevel == 1)
        return level1.getCamera();
    else //not in a level!
        return NULL;
}

double Levels::getCurrDoor(int door) {
    if (CurrLevel == 1)
        return level1.getCurrDoor(door);
    else //not in a level!
        return 1;
}

void Levels::setCurrDoor(int door, double currDoor) {
    if (CurrLevel == 1)
        level1.setCurrDoor(door,currDoor);
}

int Levels::getLevelWidth() {
    if (CurrLevel == 1)
        return level1.getLevelWidth();
    else //not in a level!
        return 1;
}

Texture * Levels::getForeground() {
    if (CurrLevel == 1)
        return level1.getForeground();
    else //not in a level!
        return NULL;
}