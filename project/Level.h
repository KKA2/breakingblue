// Level.h
// Interface for Level class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _LEVEL
#define _LEVEL

#include "Texture.h"
#include "Text.h"

using namespace std;

class Level {
public:
    Level();
    ~Level();
    void playMusic(); // play level music
    // virtual functions to be expanded
    virtual void setUp(SDL_Renderer *); // set up all textures/music to render
    virtual void display(); // draw all textures onto the screen
    // pure virtual function to be implemented lower in the hierarchy
    virtual void loadMedia() = 0;
    // utility functions
    SDL_Texture * loadTexture(string);
    // get/set functions
    void setBackground(string);
    SDL_Texture * getBackground();
    void setLevelWidth(int);
    int getLevelWidth();
    void setLevelHeight(int);
    int getLevelHeight();
    void setCameraX(int);
    int getCameraX();
    void setCameraY(int);
    int getCameraY();
    SDL_Rect * getCamera();
    void setMusic(Mix_Music *);
    Mix_Music * getMusic();
private:
    SDL_Renderer *Renderer; // window renderer
    SDL_Texture *Background; // base background texture image
    SDL_Rect Camera; // current screen on texture to be rendered
    Mix_Music *Music; // level music

    int LevelWidth;
    int LevelHeight;
};

#endif