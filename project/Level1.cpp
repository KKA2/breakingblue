// Level1.cpp
// Implementation of Level1 derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "Levels.h"
#include "Level1.h"

using namespace std;

Level1::Level1() {
	Levels::setLWidth(LEVEL_WIDTH);
}

Level1::~Level1() {}

void Level1::loadMedia() {
    Levels::setBackground(Levels::loadTexture("imgs/background.png"));
    Levels::setForeground("imgs/lvls/level1door.png");
    Levels::setMusic(Mix_LoadMUS("sound/intro.wav"));
}