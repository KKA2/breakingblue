// Enemy.h
// Interface of Enemy Class; inherits from Person class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _ENEMY
#define _ENEMY

#include "Person.h"

using namespace std;

class Enemy : public Person {
public:
    Enemy();
    ~Enemy();
    void setUp(SDL_Renderer *);
    void loadMedia(); // load all textures from path names
    void draw(int,int,int);
    int move(int,int); // return change in x position
private:
    // life bar rectangle/texture
    SDL_Rect Life[21];
    Texture LifeTexture;

    int NumSteps;
};

#endif