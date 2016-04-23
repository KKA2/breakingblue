// Master.h
// Interface for Master class to control gameplay
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
#include <cmath>
#include "Player.h"
#include "Sound.h"
#include "Levels.h"

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 400;

class Master {
public:
    Master();
    ~Master();
    void init();
    void loadMedia();

    void reset(); // reset/initially set all game attributes
    void animate(); // play any sequential animations
    void checkKeyboard(); // check keyboard for motion
    void play(); // play game

    int moveFigure(const double,const double,bool=true); // change figure position, only check new position if bool set to false
    void update();
    void updateCamera();
    // collision detection
    int checkCollision(); // checks for right/left/top collisions with foreground
    void fixCollision(int collisionType); // respond to collision
    int checkGround();
private:
    SDL_Window *Window; // window rendering to
    SDL_Renderer *Renderer; // window renderer
    Sound sound;
    Player player;
    Levels levels;
};

#endif