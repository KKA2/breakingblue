// Player.cpp
// Implementation of Player Class; inherits from Person class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Player.h"

using namespace std;

Player::Player() {}

Player::~Player() {
    LifeTexture.free();
}

void Player::setUp(SDL_Renderer *renderer) {
    Person::setUp(renderer);
    LifeTexture.setUp(renderer);
}

void Player::loadMedia() {
    Person::loadMedia();
    RunningTexture.loadFromFile("imgs/figs/blue/running.png");
    StandingTexture.loadFromFile("imgs/figs/blue/standing.png");
    JumpingTexture.loadFromFile("imgs/figs/blue/jumping.png");
    DuckingTexture.loadFromFile("imgs/figs/blue/ducking.png");
    RollingTexture.loadFromFile("imgs/figs/blue/rolling.png");
    PunchingTexture.loadFromFile("imgs/figs/blue/punching.png");
    KickingTexture.loadFromFile("imgs/figs/blue/kicking.png");
    FlyingTexture.loadFromFile("imgs/figs/blue/flying.png");
    LifeTexture.loadFromFile("imgs/figs/life.png");
}

void Player::draw(int camX, int camY, int level) {
    Person::draw(camX,camY);
    if (level == 4) {
        LifeTexture.render(Person::getXPos()-62,Person::getYPos()-100,Person::getLife());
    }
} 
