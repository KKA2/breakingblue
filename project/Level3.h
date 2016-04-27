// Level3.h
// Interface for Level3 derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _LEVEL3
#define _LEVEL3

#include "Level.h"
#include "Texture.h"

using namespace std;

class Level3 : public Level {
public:
    Level3();
    ~Level3();
    // implement virtual functions of Level class
    void setUp(SDL_Renderer *);
    void display();
    void loadMedia();
    // get/set functions
    Texture * getForeground();
    void setCurrText();
    void setCurrMaze();
private:
    Texture Foreground[5];
    Texture PurpleFigTexture;
    SDL_Rect PurpleFig;
    int CurrMaze;
};

#endif