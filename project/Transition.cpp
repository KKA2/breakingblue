// Transition.cpp
// Implementation of Transition derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Transition.h"

using namespace std;

Transition::Transition() {}

Transition::~Transition() {
    for (int f=0;f<6;f++)
        Foreground[f].free();
}

void Transition::setUp(SDL_Renderer *renderer) {
    Renderer = renderer;
    // set up renderer on all textures
    Level::setUp(renderer);
    for (int f=0;f<6;f++)
        Foreground[f].setUp(renderer);
    // set to fit screen
    Level::setLevelWidth(1000);
    Level::setLevelHeight(400);
    Level::setCameraX(0);
    Level::setCameraY(0);
}

void Transition::display() {
    Level::display();
}

void Transition::loadMedia() {
    // set up media from Level class
    Level::setBackground("imgs/bg/transition.png");
    Level::setMusic(Mix_LoadMUS("sound/techno.wav")); // music for menu screen

    // load all foreground textures
    Foreground[0].loadFromFile("imgs/transitions/menu.png");
    Foreground[1].loadFromFile("imgs/transitions/lvl1.png");
    Foreground[2].loadFromFile("imgs/transitions/lvl2.png");
    Foreground[3].loadFromFile("imgs/transitions/lvl3.png");
    Foreground[4].loadFromFile("imgs/transitions/lose.png");
    Foreground[5].loadFromFile("imgs/transitions/win.png");
}

void Transition::display(int level, int status) {
    SDL_RenderClear(Renderer); // clear screen to redraw
    display(); // call other display function to draw background
    // call display of Level class
    SDL_Rect cam = *Level::getCamera();
    // draw foreground
    getForeground(level,status)->render(0,0,&cam);
    SDL_RenderPresent(Renderer); // update screen
}

Texture * Transition::getForeground(int level, int status) {
    // get foreground corresponding to the level the player is at
    if (level == 0) // menu
        return &Foreground[0];
    else if (level == 1) // after level 1
        return &Foreground[1];
    else if (level == 2) // after level 2
        return &Foreground[2];
    else if (level == 3) // after level 3
        return &Foreground[3];
    // after level 4
    else if (status == 0) // lost after level 4
        return &Foreground[4];
    else //if (status == 1) // won after level 4
        return &Foreground[5];
}