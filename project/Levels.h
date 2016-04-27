// Levels.h
// Interface for Levels class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _LEVELS
#define _LEVELS

#include "Texture.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"

using namespace std;

class Levels {
public:
    Levels();
    ~Levels();
    // all levels
    void setUp(SDL_Renderer *); // set up renderer for all level textures
    void loadMedia(); // load media from all levels
    // level specific
    void display(bool=true); // display current level, default showtext to true
    void playMusic(); // play music associated to current level
    void stopMusic(); // stop music currently playing
    // get/set functions
    int getCurrLevel();
    void setCurrLevel(int);
    Texture * getForeground(); // get associated foreground to current level
    void setCurrText(int); // set text
    int getCurrText();
    int getTotalText();
    void setCurrMaze(); // maze
    void setCameraX(int);
    int getCameraX();
    void setCameraY(int);
    int getCameraY();
    SDL_Rect * getCamera();
    double getCurrDoor(int);
    void setCurrDoor(int,double);
    int getLevelWidth();
    int getLevelHeight();
private:
    int CurrLevel; // current level of player
    Level1 level1; // level 1
    Level2 level2;
    Level3 level3;
    Level4 level4;
};

#endif
