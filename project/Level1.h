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
    double getCurrDoor(int);
    void setCurrDoor(int,double);
    int getLevelWidth();

private:
    Texture Door1Texture;
    Texture Door2Texture;
    Texture Door3Texture;

    double CurrDoor; // store current relevant door (which one hasn't been knocked down)
    double CurrDoor1;
    double CurrDoor2;
    double CurrDoor3;
};

#endif