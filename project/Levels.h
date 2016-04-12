// Levels.h
// Interface for Levels Class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _LEVELS
#define _LEVELS

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "Texture.h"

using namespace std;

class Levels {
public:
    Levels();
    ~Levels();
    SDL_Texture * loadTexture(string);
    void setUp(SDL_Window *,SDL_Renderer *);
    void display();
    void playMusic();
    void setBackground(SDL_Texture *);
    SDL_Texture * getBackground();
    void setForeground(string);
    Texture * getForeground();
    void setCameraX(int);
    int getCameraX();
    void setMusic(Mix_Music *);
    Mix_Music * getMusic();
    virtual void loadMedia() = 0;
    int getLevelW();
    SDL_Rect * getNewCam();
    void setLWidth(int);
private:
    SDL_Window *Window; // window rendering to
    SDL_Renderer *Renderer; // window renderer
    SDL_Texture *Background;
    Texture Foreground;
    SDL_Rect Camera;
    Mix_Music *Music;
    int lWidth;
};

#endif