// Person.cpp
// Implementation of Person class; provides stick figures
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Person.h"
#include "Master.h"

using namespace std;

Person::Person() {
    // initialize all values to default
    LifePts = 200;
    XPos = -75; // directly out of bounds (so not drawn)
    YPos = -94;
    CurrRun = 0;
    CurrRoll = 0;
    CurrPunch = 0;
    CurrKick = 0;
    MoveDir = SDL_FLIP_NONE;
    State = 0;
    JumpDir = 0;
    JumpHeight = 0;
    JumpChange = 0;
    MaxJumpHeight = 140;
    FlyingEnabled = false;
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
    FlyingTexture.free();
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
    FlyingTexture.setUp(renderer);
}

void Person::loadMedia() {
    // create bounding rectangles for frames
    for (int i=0;i<7;i++) {
        Running[i].x = 75*i;
        Running[i].y = 0;
        Running[i].w = 75;
        Running[i].h = 94;
    }
    Standing.x = 0; Standing.y = 0; Standing.w = 75; Standing.h = 94;
    Jumping.x = 0; Jumping.y = 0; Jumping.w = 75; Jumping.h = 94;
    Ducking.x = 0; Ducking.y = 0; Ducking.w = 75; Ducking.h = 94;
    for (int i=0;i<8;i++) {
        Rolling[i].x = 75*i;
        Rolling[i].y = 0;
        Rolling[i].w = 75;
        Rolling[i].h = 94;
    }
    for (int i=0;i<13;i++) {
        Punching[i].x = 75*i;
        Punching[i].y = 0;
        Punching[i].w = 75;
        Punching[i].h = 94;
    }
    for (int i=0;i<11;i++) {
        Kicking[i].x = 75*i;
        Kicking[i].y = 0;
        Kicking[i].w = 75;
        Kicking[i].h = 94;
    }
    Flying.x = 0; Flying.y = 0; Flying.w = 75; Flying.h = 94;
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
        FlyingTexture.render(XPos-camX,YPos-camY,&Flying,MoveDir);
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
            texture = &FlyingTexture;
        default: // assume standing
            texture = &StandingTexture;
            break;
    }
    return texture;
}

int Person::getLifePts() const {
    return LifePts;
}

void Person::setLifePts(const int lifePts) {
    LifePts = lifePts;
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

double Person::getJumpChange() const {
    return JumpChange;
}

void Person::setJumpChange(const double jumpChange) {
    JumpChange = jumpChange;
}

int Person::getMaxJumpHeight() const {
    return MaxJumpHeight;
}

void Person::setMaxJumpHeight(const int maxJumpHeight) {
    MaxJumpHeight = maxJumpHeight;
}

bool Person::getFlyingEnabled() const {
    return FlyingEnabled;
}

void Person::setFlyingEnabled(const bool flyingEnabled) {
    FlyingEnabled = flyingEnabled;
}
