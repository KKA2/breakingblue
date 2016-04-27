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

    Level::setLevelWidth(1000);
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

    Tutorial.display();
}

void Level4::loadMedia() {
    // set up media from Level class
    Level::setBackground("imgs/bg/lvl1.png"); // PLACEHOLDER
    Level::setMusic(Mix_LoadMUS("sound/thunderous.wav"));
    // load all foreground textures
    Foreground.loadFromFile("imgs/lvl4/base1.png"); // PLACEHOLDER

    Tutorial.loadText("imgs/lvl4/txt/0.png");
    Tutorial.setTotalText(1);
}

Texture * Level4::getForeground() {
    // get foreground
    return &Foreground;
}
void Level4::setCurrText() {
    Tutorial.setCurrText(Tutorial.getCurrText() + 1); // increment currText
}
