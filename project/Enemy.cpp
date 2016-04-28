// Enemy.cpp
// Implementation of Enemy Class; inherits from Person class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Enemy.h"
#include "Master.h"
#include <cmath>

using namespace std;

Enemy::Enemy() {}

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

}

void Enemy::draw(int camX, int camY, int level) {
    Person::draw(camX,camY);
    if (level == 4) {
        LifeTexture.render(camX+SCREEN_WIDTH-220,20,Person::getLife());
    }
}

int Enemy::move(int playerXPos, int playerState) {
    int chX = 0;
    int xPos = Person::getXPos();
    int choice;
    bool playerAttack = false;
    if (playerState == 5 || playerState == 6)
        playerAttack = true;

    if (abs(playerXPos-xPos) < 100) { // if player is close by
        choice = rand()%100;
        // if running/standing (not jumping/attacking/rolling)
        if (Person::getState() <= 1) {
            if (playerAttack) { // if player is attacking, respond
                if (choice < 35) { // jump away (35% chance)
                    Person::setState(2);
                    if (Person::getJumpHeight() == 0) // if not already jumping
                        Person::setJumpDir(-1); // start moving upwards
                }
                else if (choice < 70) { // roll away (35% chance)
                    Person::setState(4);
                }
                else if (choice < 95) { // punch (25% chance)
                    Person::setState(5);
                }
                else { // kick (5% chance)
                    Person::setState(6);
                }
            }
            else if (playerState != 7) { // player not attacking or flying
                if (choice < 75) // punch (75%)
                    Person::setState(5);
                else // kick (25%)
                    Person::setState(6);
            }
        }
    }
    if (playerXPos-xPos < 0) { // player to the left of the enemy
        if (Person::getJumpHeight() != 0) { // if jumping
            chX = 4; // move to the right
        }
        else if (Person::getState() == 4) { // if rolling & not jumping
            Person::setMoveDir(SDL_FLIP_NONE); // turn to the right (move away)
        }
        else {
            Person::setMoveDir(SDL_FLIP_HORIZONTAL); // turn to the left
            if (Person::getState() != 5) { // not punching
                Person::setState(1); // set to running state
                Person::setCurrRun(Person::getCurrRun() + .3); // change frame
                chX = -2; // move to the left
            }
        }
    }
    else if (playerXPos-xPos > 0) { // player to the right of the enemy
        if (Person::getJumpHeight() != 0) { // if jumping
            chX = -4; // move to the left
        }
        else if (Person::getState() == 4) { // if rolling
            Person::setMoveDir(SDL_FLIP_HORIZONTAL); // turn to the left (move away)
        }
        else {
            Person::setMoveDir(SDL_FLIP_NONE); // turn to the left
            if (Person::getState() != 5) { // not punching
                Person::setState(1); // set to running state
                Person::setCurrRun(Person::getCurrRun() + .3); // change frame
                chX = 2; // move to the left
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
