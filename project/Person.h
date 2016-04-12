// Breaking Blue
// Person.h

#ifndef _PERSON
#define _PERSON

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "Texture.h"

using namespace std;

class Person {
public:
    Person();
    ~Person();
    void setUp(SDL_Window *,SDL_Renderer *);
    void loadMedia();
    void draw(int);

    double getXPos() const;
    void setXPos(const double);
    double getYPos() const;
    void setYPos(const double);
    double getCurrRun() const;
    void setCurrRun(const double);
    double getCurrRoll() const;
    void setCurrRoll(const double);
    double getCurrPunch() const;
    void setCurrPunch(const double);
    SDL_RendererFlip getMoveDir() const;
    void setMoveDir(const SDL_RendererFlip);
    int getState() const;
    void setState(const int);
    int getJumpDir() const;
    void setJumpDir(const int);
    double getJumpHeight() const;
    void setJumpHeight(const double);

private:
    SDL_Window *Window;
    SDL_Renderer *Renderer;

    SDL_Rect Running[7];
    Texture RunningTexture;
    SDL_Rect Standing;
    Texture StandingTexture;
    SDL_Rect Jumping;
    Texture JumpingTexture;
    SDL_Rect Ducking;
    Texture DuckingTexture;
    SDL_Rect Rolling[8];
    Texture RollingTexture;
    SDL_Rect Punching[11];
    Texture PunchingTexture;

    double XPos;
    double YPos;
    double CurrRun;
    double CurrRoll;
    double CurrPunch;
    double CurrFlip;
    SDL_RendererFlip MoveDir;
    // 0=standing, 1=running, 2=jumping, 3=ducking, 4=rolling, 5=punching
    int State;
    int JumpDir;
    double JumpHeight;
};

#endif