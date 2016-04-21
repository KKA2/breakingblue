// Level1.h
// Interface for Level1 derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _LEVEL1
#define _LEVEL1

#include "Levels.h"
#include "Texture.h"

using namespace std;

const int LEVEL_WIDTH = 4000;
const int LEVEL_HEIGHT = 400;

class Level1 : public Levels {
public:
    Level1();
    ~Level1();
    void setUp(SDL_Window *,SDL_Renderer *);
    void display();
    void loadMedia();
    void setForeground(string);
    Texture * getForeground();
    double getCurrDoor();
    void setCurrDoor(double);
    double getCurrDoor1();
    void setCurrDoor1(double);
    int getLevelWidth();

private:
    SDL_Window *Window; // window rendering to
    SDL_Renderer *Renderer; // window renderer
    Texture Door1Texture;
    SDL_Rect Door1[6];
    Texture Door2Texture;
    Texture Door3Texture;

    double currDoor; // store current relevant door (which one hasn't been knocked down)
    double currDoor1; // frame of door1
};

#endif