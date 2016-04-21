// Level.h
// Interface for Level class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _LEVEL
#define _LEVEL

#include "Texture.h"

using namespace std;

class Level {
public:
    Level();
    ~Level();
    virtual SDL_Texture * loadTexture(string);
    virtual void setUp(SDL_Window *,SDL_Renderer *);
    virtual void display(int);
    void playMusic();
    void setBackground(string);
    SDL_Texture * getBackground();
    void setCameraX(int);
    int getCameraX();
    SDL_Rect * getCamera();
    void setMusic(Mix_Music *);
    Mix_Music * getMusic();
    virtual void loadMedia() = 0;
    virtual Texture * getText();
    void setText(string);
private:
    SDL_Window *Window; // window rendering to
    SDL_Renderer *Renderer; // window renderer
    SDL_Texture *Background;
    Texture *text;
    SDL_Rect Camera;
    Mix_Music *Music;
};

#endif