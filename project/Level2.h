// Level2.h
// Interface for Level2 derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _LEVEL2
#define _LEVEL2

#include "Level.h"
#include "Texture.h"

using namespace std;

class Level2 : public Level {
public:
    Level2();
    ~Level2();
    // implement virtual functions of Level class
    void setUp(SDL_Renderer *);
    void display();
    void display(bool);
    void loadMedia();
    // get/set functions
    Texture * getForeground();
    double getCurrDoor(int);
    void setCurrDoor(int,double);
    void setCurrText();
    void setCurrText(int);
private:
    Texture Foreground[4];
    Texture Door1Texture;
    Texture Door2Texture;
    Texture Door3Texture;
    
    double CurrDoor; // current relevant door (which one hasn't been knocked down)
    // state of respective door (how many hits landed - 0.2 added for each hit)
    double CurrDoor1;
    double CurrDoor2;
    double CurrDoor3;
};

#endif
