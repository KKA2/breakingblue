// Level4.h
// Interface for Level4 derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _LEVEL4
#define _LEVEL4

#include "Level.h"
#include "Texture.h"

using namespace std;

class Level4 : public Level {
public:
    Level4();
    ~Level4();
    // implement virtual functions of Level class
    void setUp(SDL_Renderer *);
    void display();
    void loadMedia();
    // get/set functions
    Texture * getForeground();
    void setCurrText();
private:
    Texture Foreground;
};

#endif
