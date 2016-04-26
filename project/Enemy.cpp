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
}

Enemy::~Enemy() {
    LifeTexture.free();
}

void Enemy::setUp(SDL_Renderer *renderer) {
    Person::setUp(renderer);
    LifeTexture.setUp(renderer);
}

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

    LifeTexture.loadFromFile("imgs/figs/life.png");
    for (int i=0;i<201;i++) {
        Life[i].x = 0;
        Life[i].y = 10*i;
        Life[i].w = 200;
        Life[i].h = 10;
    }
}

void Enemy::draw(int camX, int camY, int level) {
    Person::draw(camX,camY);
    if (level == 4) {
        LifeTexture.render(camX+SCREEN_WIDTH-220,20,&Life[200-Person::getLifePts()]);
    }
}

int Enemy::move(int playerXPos, int playerState) {
    int chX = 0;
    int xPos = Person::getXPos();
    int choice;

    if (playerState == 5 && abs(playerXPos-xPos) < 100) { // if player is punching and close by
        choice = rand()%12;
        if (choice == 0) { // jump
            Person::setState(2);
            if (Person::getJumpHeight() == 0) // if not already jumping
                Person::setJumpDir(-1); // start moving upwards
        }
        else { // roll
            Person::setState(4);
        }
    }
    else if (playerState == 0 && abs(playerXPos-xPos) < 100) // if close to standing player
        Person::setState(5); // set state to punching

    if (playerXPos-xPos < 0) { // player to the left of the enemy
        if (Person::getState() == 4) { // if rolling
            Person::setMoveDir(SDL_FLIP_NONE); // turn to the right (move away)
        }
        else if (Person::getState() == 2) { // if jumping
            chX = 4; // move to the left
        }
        else {
            if (Person::getState() != 5) { // not punching/rolling
                if (Person::getState() != 2) { // not jumping
                    Person::setMoveDir(SDL_FLIP_HORIZONTAL); // turn to the left
                    Person::setState(1); // set to running state
                    Person::setCurrRun(Person::getCurrRun() + .3); // change frame
                    chX = -2; // move to the left
                }
                else {
                    chX = 4;
                }
            }
        }
    }
    else if (playerXPos-xPos > 0) { // player to the right of the enemy
        if (Person::getState() == 4) { // if rolling
            Person::setMoveDir(SDL_FLIP_HORIZONTAL); // turn to the left (move away)
        }
        else if (Person::getState() == 2) { // if jumping
            chX = -4; // move to the right
        }
        else {
            if (Person::getState() != 5) { // not punching
                Person::setMoveDir(SDL_FLIP_NONE); // turn to the right
                Person::setState(1);
                Person::setCurrRun(Person::getCurrRun() + .3);
                chX = 2; // move to the right
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
