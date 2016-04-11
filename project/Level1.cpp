// Breaking Blue
// Level1.cpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "Levels.h"
#include "Level1.h"

using namespace std;

Level1::Level1() {}

Level1::~Level1() {}

void Level1::loadMedia() {
    Levels::setBackground(Levels::loadTexture("imgs/background.png"));
    Levels::setForeground(Levels::loadTexture("imgs/lvls/level1.png"));
    Levels::setMusic(Mix_LoadMUS("sound/intro.wav"));
}