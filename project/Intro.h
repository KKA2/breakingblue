// Intro.h
// Interface for Intro derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _INTRO
#define _INTRO

#include "Texture.h"
#include "Level.h"

using namespace std;

class Intro : public Level {
public:
    Intro();
    ~Intro();
    // implement virtual functions of Level class
    void setUp(SDL_Renderer *);
    void loadMedia();
    void display();

    void animate();

private:
    SDL_Renderer *Renderer;
    Texture Foreground[23];

    int CurrScene; // first scene of sequence of scenes currently displaying on screen
    int NumScenes; // number of scenes to display on a screen
};

#endif
