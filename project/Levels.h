// Levels.h
// Interface for Levels class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _LEVELS
#define _LEVELS

#include "Texture.h"
#include "Level1.h"

using namespace std;

class Levels {
public:
    Levels();
    ~Levels();
    void setUp(SDL_Window *,SDL_Renderer *);
    void loadMedia();

    void display();
    void playMusic();

    int getCurrLevel();
    void setCurrLevel(int);
    void setCurrDir();
    void setCameraX(int);
    int getCameraX();
    SDL_Rect * getCamera();
    double getCurrDoor(int);
    void setCurrDoor(int,double);
    int getLevelWidth();

    Texture * getForeground();

private:
    int CurrLevel;
    Level1 level1;
};

#endif
