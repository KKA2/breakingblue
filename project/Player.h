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
    void loadMedia(); // load all textures from path names
private:
};

#endif