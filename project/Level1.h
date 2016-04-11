// Breaking Blue
// Level1.h

#ifndef _LEVEL1
#define _LEVEL1

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "Levels.h"

using namespace std;

class Level1 : public Levels {
public:
    Level1();
    ~Level1();
    void loadMedia();
    void loadTexture();

private:
};

#endif