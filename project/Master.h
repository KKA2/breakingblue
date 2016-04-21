// Master.h
// Interface for Master class to control gameplay
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _MASTER
#define _MASTER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <cmath>
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

    int moveFigure(const double,const double,bool=true);
    void update();
    void updateCamera();

    int checkCollision(Person * person, Level1 *level1); // checks for right/left/top collisions with foreground
    void fixCollision(Person *person, int collisionType); // respond to collision
    int checkGround(Person * person, Level1 *level1);

private:
    SDL_Window *Window; // window rendering to
    SDL_Renderer *Renderer; // window renderer
    //Sound sound;
    Person person;
    Level1 level1;
};

#endif