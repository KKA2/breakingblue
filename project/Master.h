// Ann Keenan
// Feb 29

#ifndef _MASTER
#define _MASTER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "Person.h"
#include "Sound.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 500;

class Master {
public:
    Master();
    ~Master();
    void init();
    void loadMedia();
    SDL_Texture *loadTexture(string path);
    void update(int,int,int,int,SDL_RendererFlip);
    void playSound(int);
    void playMusic(int);
    void stopMusic();

private:
    SDL_Window *Window; // window rendering to
    SDL_Renderer *Renderer; // window renderer
    SDL_Texture *Background;

    Person person;
    Sound sound;
};

#endif