// Level4.cpp
// Implementation of Level4 derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Level4.h"

using namespace std;

Level4::Level4() {}

Level4::~Level4() {
    Foreground.free();
}

void Level4::setUp(SDL_Renderer *renderer) {
    // set up renderer on all textures
    Level::setUp(renderer);
    Foreground.setUp(renderer);

    Level::setLevelWidth(4000);
    Level::setLevelHeight(400);
    Level::setCameraX(0);
    Level::setCameraY(0);
}

void Level4::display() {
    // call display of Level class
    Level::display();
    // get current camera display
    SDL_Rect cam = *Level::getCamera();
    // render foreground onto screen
    getForeground()->render(0,0,&cam);
}

void Level4::loadMedia() {
    // set up media from Level class
    Level::setBackground("imgs/bg/level1.png"); // PLACEHOLDER
    Level::setMusic(Mix_LoadMUS("sound/suspense.wav"));
    // load all foreground textures
    Foreground.loadFromFile("imgs/lvl1/base4.png"); // PLACEHOLDER
}

Texture * Level4::getForeground() {
    // get foreground
    return &Foreground;
}

int Level4::getLevelWidth() {
    return Level::getLevelWidth();
}

int Level4::getLevelHeight() {
    return Level::getLevelHeight();
}
