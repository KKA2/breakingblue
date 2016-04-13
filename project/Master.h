// Master.h
// Interface for Master Class to control gameplay
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _MASTER
#define _MASTER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "Person.h"
#include "Sound.h"
#include "Level1.h"

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 400;

class Master {
public:
    Master();
    ~Master();
    void init();
    void loadMedia();

    void play();

    int moveFigure(const double,const double);
    void update();
    void updateCamera();

    int checkCollision(Person * person, Level1 *level1); //ensures figures stay on ground level
    int checkGround(Person * person, Level1 *level1);

private:
    SDL_Window *Window; // window rendering to
    SDL_Renderer *Renderer; // window renderer
    Sound sound;
    Person person;
    Level1 level1;
};

#endif