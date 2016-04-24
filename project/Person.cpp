// Person.cpp
// Implementation of Person class; provides stick figures
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Person.h"
#include "Master.h"

using namespace std;

Person::Person() {
    // initialize all values to default
    XPos = 0;
    YPos = 0;
    CurrRun = 0;
    CurrRoll = 0;
    CurrPunch = 0;
    CurrKick = 0;
    MoveDir = SDL_FLIP_NONE;
    State = 0;
    JumpDir = 0;
    JumpHeight = 0;
    MaxJumpHeight = 120;
}

Person::~Person() {
    // free all textures
    RunningTexture.free();
    StandingTexture.free();
    JumpingTexture.free();
    DuckingTexture.free();
    RollingTexture.free();
    PunchingTexture.free();
    KickingTexture.free();
}

void Person::setUp(SDL_Renderer *renderer) {
    // allow for textures to render to screen
    RunningTexture.setUp(renderer);
    StandingTexture.setUp(renderer);
    JumpingTexture.setUp(renderer);
    DuckingTexture.setUp(renderer);
    RollingTexture.setUp(renderer);
    PunchingTexture.setUp(renderer);
    KickingTexture.setUp(renderer);
}

void Person::draw(int camX, int camY) {
    if (State == 0)
        StandingTexture.render(XPos-camX,YPos-camY,&Standing,MoveDir);
    else if (State == 1)
        RunningTexture.render(XPos-camX,YPos-camY,&Running[int(CurrRun)],MoveDir);
    else if (State == 2)
        JumpingTexture.render(XPos-camX,YPos-camY,&Jumping,MoveDir);
    else if (State == 3)
        DuckingTexture.render(XPos-camX,YPos-camY,&Ducking,MoveDir);
    else if (State == 4)
        RollingTexture.render(XPos-camX,YPos-camY,&Rolling[int(CurrRoll)],MoveDir);
    else if (State == 5)
        PunchingTexture.render(XPos-camX,YPos-camY,&Punching[int(CurrPunch)],MoveDir);
    else if (State == 6)
        KickingTexture.render(XPos-camX,YPos-camY,&Kicking[int(CurrKick)],MoveDir);
    else if (State == 7) // flying
        JumpingTexture.render(XPos-camX,YPos-camY,&Jumping,MoveDir); // WILL CHANGE
}

void Person::setInitialPos(int width, int height) {
    XPos = 0;
    YPos = height - SCREEN_HEIGHT;
}

Texture * Person::getTexture(const int state) {
    Texture * texture;
    switch (state) {
        case 0: // standing
            texture = &StandingTexture;
            break;
        case 1: // running
            texture = &RunningTexture;
            break;
        case 2: // jumping
            texture = &JumpingTexture;
            break;
        case 3: // ducking
            texture = &DuckingTexture;
            break;
        case 4: // rolling
            texture = &RollingTexture;
            break;
        case 5: // punching
            texture = &PunchingTexture;
            break;
        case 6: // kicking
            texture = &KickingTexture;
        case 7: // flying
            texture = &JumpingTexture;
        default: // assume standing
            texture = &StandingTexture;
            break;
    }
    return texture;
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

double Person::getCurrKick() const {
    return CurrKick;
}

void Person::setCurrKick(const double currKick) {
    CurrKick = currKick;
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

double Person::getJumpHeight() const {
    return JumpHeight;
}

void Person::setJumpHeight(const double jumpHeight) {
    JumpHeight = jumpHeight;
}

int Person::getMaxJumpHeight() const {
    return MaxJumpHeight;
}

void Person::setMaxJumpHeight(const int maxJumpHeight) {
    MaxJumpHeight = maxJumpHeight;
}