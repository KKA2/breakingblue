// Level.h
// Interface for Outro class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _OUTRO
#define _OUTRO

#include "Texture.h"
#include "Level.h"

using namespace std;

class Outro : public Level {
public:
    Outro();
    ~Outro();
    void setUp(SDL_Renderer *);
    void loadMedia();
    void display(); // display the scene w/ opacity texture overlay
    void animate(); // animate the outro
    void show(); // show scene
    void hide(); // hide scene
private:
    SDL_Renderer *Renderer; // window renderer
    Texture Fade[11]; // fade textures array
    Texture Scene[3]; // backgrounds of outro
    int CurrScene; // current background displaying
    int CurrFade; // current texture
};

#endif