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

void Enemy::setInitialPos(int width,int height) {
    Person::setXPos(width-75);
    Person::setYPos(height - SCREEN_HEIGHT);
}
void Enemy::move(int playerXPos, int playerYPos) {

}
