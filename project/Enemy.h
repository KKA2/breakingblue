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
    void loadMedia(); // load all textures from path names
    void setInitialPos(int,int);
    void move(int,int);
private:
};

#endif