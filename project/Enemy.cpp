// Enemy.cpp
// Implementation of Enemy Class; inherits from Person class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Enemy.h"
#include "Master.h"
#include <cmath>

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
    FlyingTexture.loadFromFile("imgs/figs/red/flying.png");
}

int Enemy::move(int playerXPos, int playerState) {
    int chX = 0;
    int xPos = Person::getXPos();

    if (playerState == 5) { // if player is punching
        Person::setState(2); // jump over punch
        if (Person::getJumpHeight() == 0) // if not already jumping
            Person::setJumpDir(-1); // start moving upwards
    }
    else if (abs(playerXPos-xPos) < 40 && playerState == 0) // if close to standing player
        Person::setState(5); // set state to punching

    if (playerXPos-xPos < 0) { // player to the left of the enemy
        Person::setMoveDir(SDL_FLIP_HORIZONTAL); // turn to the left
        if (Person::getState() != 5) { // not punching
            if (Person::getState() != 2) { // not jumping
                Person::setState(1); // set to running state
                Person::setCurrRun(Person::getCurrRun() + .3); // change frame
                chX = -2; // move to the left
            }
            else {
                chX = 2;
            }
        }
    }
    else if (playerXPos-xPos > 0) { // player to the right of the enemy
        Person::setMoveDir(SDL_FLIP_NONE); // turn to the right
        if (Person::getState() != 5) { // not punching
            if (Person::getState() != 2) { // not jumping
                Person::setState(1);
                Person::setCurrRun(Person::getCurrRun() + .3);
                chX = 2;
            }
            else {
                chX = -2; // move to the right
            }
        }
    }
    else { // on top (error check)
        Person::setCurrRun(0); // reset frame count
    }

    if (Person::getCurrRun() >= 7) // keep in bounds of array for running
        Person::setCurrRun(0);

    return chX; // return change in x position
}
