// Person.h
// Interface of Person Class; provides stick figures
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _PERSON
#define _PERSON

#include "Texture.h"

using namespace std;

class Person {
public:
    Person();
    ~Person();
    void setUp(SDL_Renderer *); // set up all textures to render
    virtual void loadMedia(); // load all textures from path names
    void draw(int,int); // draw all textures onto the screen
    // get/set functions
    Texture * getTexture(const int);
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
    double getCurrKick() const;
    void setCurrKick(const double);
    SDL_RendererFlip getMoveDir() const;
    void setMoveDir(const SDL_RendererFlip);
    int getState() const;
    void setState(const int);
    int getJumpDir() const;
    void setJumpDir(const int);
    double getJumpHeight() const;
    void setJumpHeight(const double);
    int getMaxJumpHeight() const;
    void setMaxJumpHeight(const int);
    bool getFlyingEnabled() const;
    void setFlyingEnabled(const bool);
protected:
    // rectangles outlining the sprite frames within each respective texture
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
    SDL_Rect Punching[13];
    Texture PunchingTexture;
    SDL_Rect Kicking[11];
    Texture KickingTexture;
    SDL_Rect Flying;
    Texture FlyingTexture;
private:
    // position of the figure
    int XPos;
    int YPos;
    // current frame of sprite texture to draw
    double CurrRun;
    double CurrRoll;
    double CurrPunch;
    double CurrKick;
    // direction of the figure's motion
    SDL_RendererFlip MoveDir;
    // current state of animation:
    // 0=standing, 1=running, 2=jumping, 3=ducking, 4=rolling, 5=punching, 6=kicking, 7=flying
    int State;
    // rising or falling in the jump:
    // 0=not jumping, 1=down, -1=up
    int JumpDir;
    // height above initial ground level
    double JumpHeight;
    // maximum height able to jump above initial ground level
    int MaxJumpHeight;
    bool FlyingEnabled;
};

#endif