// Intro.cpp
// Implementation of introduction
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Intro.h"

using namespace std;

Intro::Intro() {

}

Intro::~Intro() {
    for (int f=0;f<1;f++)
        Foreground[f].free();
}

void Intro::setUp(SDL_Renderer *renderer) {
    Renderer = renderer;
    // set up renderer on all textures
    Level::setUp(renderer);
    for (int f=0;f<1;f++)
        Foreground[f].setUp(renderer);
    // set to fit screen
    Level::setLevelWidth(1000);
    Level::setLevelHeight(400);
    Level::setCameraX(0);
    Level::setCameraY(0);
}

void Intro::display() {
    Level::display();

    SDL_Rect cam = *Level::getCamera();
    // draw foreground
    Foreground[0].render(0,0,&cam);
    SDL_RenderPresent(Renderer); // update screen
}

void Intro::loadMedia() {
    // set up media from Level class
    Level::setBackground("imgs/bg/intro.png");
    Level::setMusic(Mix_LoadMUS("sound/techno.wav")); // music for menu screen

    // load all foreground textures
    Foreground[0].loadFromFile("imgs/intro/intro1.png");
}
