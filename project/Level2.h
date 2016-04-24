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
    void loadMedia();
    // get/set functions
    Texture * getForeground();
    void setCurrText();
private:
    Texture Foreground;
};

#endif
