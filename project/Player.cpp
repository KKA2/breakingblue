// Player.cpp
// Implementation of Player Class; inherits from Person class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Player.h"

using namespace std;

Player::Player() {}

Player::~Player() {}

void Player::loadMedia() {
    RunningTexture.loadFromFile("imgs/figs/blue/running.png");
    for (int i=0;i<7;i++) {
        Running[i].x = 75*i;
        Running[i].y = 0;
        Running[i].w = 75;
        Running[i].h = 94;
    }

    StandingTexture.loadFromFile("imgs/figs/blue/standing.png");
    Standing.x = 0; Standing.y = 0; Standing.w = 75; Standing.h = 94;

    JumpingTexture.loadFromFile("imgs/figs/blue/jumping.png");
    Jumping.x = 0; Jumping.y = 0; Jumping.w = 75; Jumping.h = 94;

    DuckingTexture.loadFromFile("imgs/figs/blue/ducking.png");
    Ducking.x = 0; Ducking.y = 0; Ducking.w = 75; Ducking.h = 94;

    RollingTexture.loadFromFile("imgs/figs/blue/rolling.png");
    for (int i=0;i<8;i++) {
        Rolling[i].x = 75*i;
        Rolling[i].y = 0;
        Rolling[i].w = 75;
        Rolling[i].h = 94;
    }

    PunchingTexture.loadFromFile("imgs/figs/blue/punching.png");
    for (int i=0;i<13;i++) {
        Punching[i].x = 75*i;
        Punching[i].y = 0;
        Punching[i].w = 75;
        Punching[i].h = 94;
    }

    KickingTexture.loadFromFile("imgs/figs/blue/kicking.png");
    for (int i=0;i<11;i++) {
        Kicking[i].x = 75*i;
        Kicking[i].y = 0;
        Kicking[i].w = 75;
        Kicking[i].h = 94;
    }
}
