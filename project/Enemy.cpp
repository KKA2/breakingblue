// Enemy.cpp
// Implementation of Enemy Class; inherits from Person class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Enemy.h"
#include "Master.h"

using namespace std;

Enemy::Enemy() {
    NumSteps = 0;
    Life = 100;
}

Enemy::~Enemy() {}

void Enemy::loadMedia() {
    Person::loadMedia();
    RunningTexture.loadFromFile("imgs/figs/red/running.png");
    StandingTexture.loadFromFile("imgs/figs/red/standing.png");
    JumpingTexture.loadFromFile("imgs/figs/red/jumping.png");
    DuckingTexture.loadFromFile("imgs/figs/red/ducking.png");
    RollingTexture.loadFromFile("imgs/figs/red/rolling.png");
    PunchingTexture.loadFromFile("imgs/figs/red/punching.png");
    KickingTexture.loadFromFile("imgs/figs/red/kicking.png");
}

void Enemy::move(int playerXPos, int &chX) {
    int xPos = Person::getXPos();

    if (playerXPos-xPos < 0) { // player to the left of the enemy
        Person::setMoveDir(SDL_FLIP_HORIZONTAL); // turn to the left
        Person::setState(1); // set to running state
        Person::setCurrRun(Person::getCurrRun() + .3); // change frame
        chX = -5; // move to the left
    }
    else if (playerXPos-xPos > 0) { // player to the right of the enemy
        Person::setMoveDir(SDL_FLIP_NONE); // turn to the right
        Person::setState(1);
        Person::setCurrRun(Person::getCurrRun() + .3);
        chX = 5; // move to the right
    }
    else {
        Person::setCurrRun(0); // reset frame count
    }

    if (Person::getCurrRun() >= 7) // keep in bounds of array for running
        Person::setCurrRun(0);
}
