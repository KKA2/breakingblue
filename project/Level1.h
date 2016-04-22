// Level1.h
// Interface for Level1 derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _LEVEL1
#define _LEVEL1

#include "Level.h"
#include "Texture.h"

using namespace std;

const int LEVEL_WIDTH = 4000;
const int LEVEL_HEIGHT = 400;

class Level1 : public Level {
public:
    Level1();
    ~Level1();
    void setUp(SDL_Window *,SDL_Renderer *);
    void display();
    void loadMedia();
    Texture * getForeground();
    double getCurrDoor(int);
    void setCurrDoor(int,double);
    int getLevelWidth();

private:
    Texture Foreground[4];
    Texture Door1Texture;
    Texture Door2Texture;
    Texture Door3Texture;
    Text missionParam;

    double CurrDoor; // store current relevant door (which one hasn't been knocked down)
    double CurrDoor1; // state of first door
    double CurrDoor2;
    double CurrDoor3;
};

#endif