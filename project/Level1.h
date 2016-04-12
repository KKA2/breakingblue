// Level1.h
// Interface for Level1 Derived Class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _LEVEL1
#define _LEVEL1

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "Levels.h"
#include "Texture.h"

using namespace std;

const int LEVEL_WIDTH = 4000;
const int LEVEL_HEIGHT = 400;

class Level1 : public Levels {
public:
    Level1();
    ~Level1();
    void loadMedia();
    void loadTexture();
private:
};

#endif