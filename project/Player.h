// Player.h
// Interface of Player Class; inherits from Person class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _PLAYER
#define _PLAYER

#include "Person.h"

using namespace std;

class Player : public Person {
public:
    Player();
    ~Player();
    void setUp(SDL_Renderer *);
    void loadMedia(); // load all textures from path names
    void draw(int,int,int);
private:
    // life bar rectangle/texture
    SDL_Rect Life[21];
    Texture LifeTexture;
};

#endif