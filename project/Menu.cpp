// Menu.cpp
// Implementation of Menu derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Menu.h"

using namespace std;

Menu::Menu() {}

Menu::~Menu() {}

void Menu::setUp(SDL_Renderer *renderer) {
    // set up renderer on all textures
    Level::setUp(renderer);
    // set to fit screen
    Level::setLevelWidth(1000);
    Level::setLevelHeight(400);
    Level::setCameraX(0);
    Level::setCameraY(0);
}

void Menu::display() {
    // call display of Level class
    Level::display();
    // get current camera display
    SDL_Rect cam = *Level::getCamera();
}

void Menu::loadMedia() {
    // set up media from Level class
    Level::setBackground("imgs/bg/menu.png");
    Level::setMusic(Mix_LoadMUS("sound/techno.wav"));
}
