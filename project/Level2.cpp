// Level2.cpp
// Implementation of Level2 derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Level2.h"

using namespace std;

Level2::Level2() {}

Level2::~Level2() {
    Foreground.free();
}

void Level2::setUp(SDL_Renderer *renderer) {
    // set up renderer on all textures
    Level::setUp(renderer);
    Foreground.setUp(renderer);

    Level::setLevelWidth(4000);
    Level::setLevelHeight(400);
    Level::setCameraX(0);
    Level::setCameraY(0);
}

void Level2::display() {
    // call display of Level class
    Level::display();
    // get current camera display
    SDL_Rect cam = *Level::getCamera();
    // render foreground onto screen
    getForeground()->render(0,0,&cam);
}

void Level2::loadMedia() {
    // set up media from Level class
    Level::setBackground("imgs/bg/lvl1.png"); // PLACEHOLDER
    Level::setMusic(Mix_LoadMUS("sound/electronic.wav"));
    // load all foreground textures
    Foreground.loadFromFile("imgs/lvl1/base4.png"); // PLACEHOLDER
}

Texture * Level2::getForeground() {
    // get foreground
    return &Foreground;
}
