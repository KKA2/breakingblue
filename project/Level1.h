// Level1.h
// Interface for Level1 derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _LEVEL1
#define _LEVEL1

#include "Level.h"
#include "Texture.h"

using namespace std;

class Level1 : public Level {
public:
    Level1();
    ~Level1();
    // implement virtual functions of Level class
    void setUp(SDL_Renderer *);
    void display();
    void loadMedia();
    // get/set functions
    Texture * getForeground();
    double getCurrDoor(int);
    void setCurrDoor(int,double);
    int getLevelWidth();
    int getLevelHeight();
    void setCurrText();
private:
    // foregrounds containing or mission each door
    // 0=all doors, 1=first door gone, 2=second door gone, 3=all doors gone
    Texture Foreground[4];
    // animation sprites for each door
    Texture Door1Texture;
    Texture Door2Texture;
    Texture Door3Texture;
    Text MissionParam; // text for mission parameters

    double CurrDoor; // current relevant door (which one hasn't been knocked down)
    // state of respective door (how many hits landed - 0.25 added for each hit)
    double CurrDoor1;
    double CurrDoor2;
    double CurrDoor3;
    int CurrText; //current text direction to be displayed
};

#endif