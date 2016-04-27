// Levels.cpp
// Implementation of Levels class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Levels.h"

using namespace std;

Levels::Levels() {
    CurrLevel = 0; // set to before any level
}

Levels::~Levels() {}

void Levels::setUp(SDL_Renderer *renderer) {
    level1.setUp(renderer);
    level2.setUp(renderer);
    level3.setUp(renderer);
    level4.setUp(renderer);
}

void Levels::loadMedia() {
    level1.loadMedia();
    level2.loadMedia();
    level3.loadMedia();
    level4.loadMedia();
}

int Levels::getCurrLevel() {
    return CurrLevel;
}

void Levels::setCurrLevel(int currLevel) {
    CurrLevel = currLevel;
}

void Levels::display(bool showText) {
    // only levels 1 and 2 have tutorial text (levels 3 and 4 display all text always)
    if (CurrLevel == 1)
        level1.display(showText);
    else if (CurrLevel == 2)
        level2.display(showText);
    else if (CurrLevel == 3)
        level3.display();
    else // if (CurrLevel == 4)
        level4.display();
}

void Levels::playMusic() {
    if (CurrLevel == 1)
        level1.playMusic();
    else if (CurrLevel == 2)
        level2.playMusic();
    else if (CurrLevel == 3)
        level3.playMusic();
    else // if (CurrLevel == 4)
        level4.playMusic();
}

void Levels::stopMusic() {
    // fade out music in 1 second
    while(!Mix_FadeOutMusic(1000) && Mix_PlayingMusic()) {
        // wait for any fades to complete
        SDL_Delay(100);
    }
}

Texture * Levels::getForeground() {
    // menu does not have a foreground
    if (CurrLevel == 1)
        return level1.getForeground();
    else if (CurrLevel == 2)
        return level2.getForeground();
    else if (CurrLevel == 3)
        return level3.getForeground();
    else // if (CurrLevel == 4)
        return level4.getForeground();
}

void Levels::setCurrText(int currText) {
    if (CurrLevel == 1)
        level1.setCurrText(currText);
    else if (CurrLevel == 2)
        level2.setCurrText(currText);
    else if (CurrLevel == 3)
        level3.setCurrText(currText);
    else if (CurrLevel == 4)
        level4.setCurrText(currText);
}

int Levels::getCurrText() {
    if (CurrLevel == 1)
        return level1.getCurrText();
    else if (CurrLevel == 2)
        return level2.getCurrText();
    else if (CurrLevel == 3)
        return level3.getCurrText();
    else // if (CurrLevel == 4)
        return level4.getCurrText();
}

int Levels::getTotalText() {
    if (CurrLevel == 1)
        return level1.getTotalText();
    else if (CurrLevel == 2)
        return level2.getTotalText();
    else if (CurrLevel == 3)
        return level3.getTotalText();
    else // if (CurrLevel == 4)
        return level4.getTotalText();
}

void Levels::setCurrMaze() {
    if (CurrLevel == 3)
        level3.setCurrMaze(); // call level3 class function
}

void Levels::setCameraX(int x) {
    if (CurrLevel == 1)
        level1.setCameraX(x);
    else if (CurrLevel == 2)
        level2.setCameraX(x);
    else if (CurrLevel == 3)
        level3.setCameraX(x);
    else // if (CurrLevel == 4)
        level4.setCameraX(x);
}

int Levels::getCameraX() {
    if (CurrLevel == 1)
        return level1.getCameraX();
    else if (CurrLevel == 2)
        return level2.getCameraX();
    else if (CurrLevel == 3)
        return level3.getCameraX();
    else // if (CurrLevel == 4)
        return level4.getCameraX();
}

void Levels::setCameraY(int y) {
    if (CurrLevel == 1)
        level1.setCameraY(y);
    else if (CurrLevel == 2)
        level2.setCameraY(y);
    else if (CurrLevel == 3)
        level3.setCameraY(y);
    else // if (CurrLevel == 4)
        level4.setCameraY(y);
}

int Levels::getCameraY() {
    if (CurrLevel == 1)
        return level1.getCameraY();
    else if (CurrLevel == 2)
        return level2.getCameraY();
    else if (CurrLevel == 3)
        return level3.getCameraY();
    else // if (CurrLevel == 4)
        return level4.getCameraY();
}

SDL_Rect * Levels::getCamera() {
    if (CurrLevel == 1)
        return level1.getCamera();
    else if (CurrLevel == 2)
        return level2.getCamera();
    else if (CurrLevel == 3)
        return level3.getCamera();
    else // if (CurrLevel == 4)
        return level4.getCamera();
}

double Levels::getCurrDoor(int door) {
    if (CurrLevel == 1)
        return level1.getCurrDoor(door);
    else if (CurrLevel == 2)
        return level2.getCurrDoor(door);
    else //not in a level
        return 0;
}

void Levels::setCurrDoor(int door, double currDoor) {
    if (CurrLevel == 1)
        level1.setCurrDoor(door,currDoor);
    else if (CurrLevel == 2)
        level2.setCurrDoor(door,currDoor);
}

int Levels::getLevelWidth() {
    if (CurrLevel == 1)
        return level1.getLevelWidth();
    else if (CurrLevel == 2)
        return level2.getLevelWidth();
    else if (CurrLevel == 3)
        return level3.getLevelWidth();
    else // if (CurrLevel == 4)
        return level4.getLevelWidth();
}

int Levels::getLevelHeight() {
    if (CurrLevel == 1)
        return level1.getLevelHeight();
    else if (CurrLevel == 2)
        return level2.getLevelHeight();
    else if (CurrLevel == 3)
        return level3.getLevelHeight();
    else // if (CurrLevel == 4)
        return level4.getLevelHeight();
}
