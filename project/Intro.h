// Intro.h
// Interface for Intro derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _Intro
#define _Intro

#include "Level.h"
#include "Texture.h"

using namespace std;

class Intro : public Level {
public:
    Intro();
    ~Intro();
    // implement virtual functions of Level class
    void setUp(SDL_Renderer *);
    void display();
    void loadMedia();
    // get/set functions
private:
    SDL_Renderer *Renderer;
    Texture Foreground[20];

};

#endif
