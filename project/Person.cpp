// Breaking Blue
// Person.cpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "Master.h"
#include "Person.h"
#include "Texture.h"

using namespace std;

Person::Person() {
    Window = NULL;
    Renderer = NULL;
    XPos = SCREEN_WIDTH/2;
    YPos = GroundLevel;
    CurrRun = 0;
    CurrRoll = 0;
    CurrPunch = 0;
    MoveDir = SDL_FLIP_NONE;
    State = 0;
    JumpDir = 0;
}

Person::~Person() {
    RunningTexture.free();
    StandingTexture.free();
    JumpingTexture.free();
    DuckingTexture.free();
    RollingTexture.free();
    PunchingTexture.free();
    BackflipTexture.free();
}

void Person::setUp(SDL_Window *window, SDL_Renderer *renderer) {
    Window = window;
    Renderer = renderer;

    RunningTexture.setUp(renderer);
    StandingTexture.setUp(renderer);
    JumpingTexture.setUp(renderer);
    DuckingTexture.setUp(renderer);
    RollingTexture.setUp(renderer);
    PunchingTexture.setUp(renderer);
    BackflipTexture.setUp(renderer);
}

void Person::loadMedia() {
    RunningTexture.loadFromFile("./imgs/figs/running.png");
    for (int i=0;i<7;i++) {
        Running[i].x = 75*i;
        Running[i].y = 0;
        Running[i].w = 75;
        Running[i].h = 94;
    }

    StandingTexture.loadFromFile("./imgs/figs/standing.png");
    Standing.x = 0; Standing.y = 0; Standing.w = 75; Standing.h = 94;

    JumpingTexture.loadFromFile("./imgs/figs/jumping.png");
    Jumping.x = 0; Jumping.y = 0; Jumping.w = 75; Jumping.h = 94;

    DuckingTexture.loadFromFile("./imgs/figs/ducking.png");
    Ducking.x = 0; Ducking.y = 0; Ducking.w = 75; Ducking.h = 94;

    RollingTexture.loadFromFile("./imgs/figs/rolling.png");
    for (int i=0;i<8;i++) {
        Rolling[i].x = 75*i;
        Rolling[i].y = 0;
        Rolling[i].w = 75;
        Rolling[i].h = 94;
    }

    PunchingTexture.loadFromFile("./imgs/figs/punching.png");
    for (int i=0;i<11;i++) {
        Punching[i].x = 75*i;
        Punching[i].y = 0;
        Punching[i].w = 75;
        Punching[i].h = 94;
    }

    BackflipTexture.loadFromFile("./imgs/figs/backflip.png");
    for (int i=0;i<26;i++) {
        Backflip[i].x = 75*i;
        Backflip[i].y = 0;
        Backflip[i].w = 75;
        Backflip[i].h = 94;
    }
}

void Person::draw(int camX) {

    if (State == 0)
        StandingTexture.render(XPos-camX,YPos,&Standing,MoveDir);
    else if (State == 1)
        RunningTexture.render(XPos-camX,YPos,&Running[int(CurrRun)],MoveDir);
    else if (State == 2)
        JumpingTexture.render(XPos-camX,YPos,&Jumping,MoveDir);
    else if (State == 3)
        DuckingTexture.render(XPos-camX,YPos,&Ducking,MoveDir);
    else if (State == 4)
        RollingTexture.render(XPos-camX,YPos,&Rolling[int(CurrRoll)],MoveDir);
    else if (State == 5)
        PunchingTexture.render(XPos-camX,YPos,&Rolling[int(CurrPunch)],MoveDir);
    else if (State == 6)
        BackflipTexture.render(XPos-camX,YPos,&Backflip[int(CurrFlip)],MoveDir);
}

double Person::getXPos() const {
    return XPos;
}
void Person::setXPos(const double xPos) {
    XPos = xPos;
}
double Person::getYPos() const {
    return YPos;
}
void Person::setYPos(const double yPos) {
    YPos = yPos;
}
double Person::getCurrRun() const {
    return CurrRun;
}
void Person::setCurrRun(const double currRun) {
    CurrRun = currRun;
}
double Person::getCurrRoll() const {
    return CurrRoll;
}
void Person::setCurrRoll(const double currRoll) {
    CurrRoll = currRoll;
}
double Person::getCurrPunch() const {
    return CurrPunch;
}
void Person::setCurrPunch(const double currPunch) {
    CurrPunch = currPunch;
}
double Person::getCurrFlip() const {
    return CurrFlip;
}
void Person::setCurrFlip(const double currFlip) {
    CurrFlip = currFlip;
}
SDL_RendererFlip Person::getMoveDir() const {
    return MoveDir;
}
void Person::setMoveDir(const SDL_RendererFlip moveDir) {
    MoveDir = moveDir;
}
int Person::getState() const {
    return State;
}
void Person::setState(const int state) {
    State = state;
}
int Person::getJumpDir() const {
    return JumpDir;
}
void Person::setJumpDir(const int jumpDir) {
    JumpDir = jumpDir;
}

