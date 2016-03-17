// Ann Keenan
// Mar 12

#ifndef _SOUND
#define _SOUND

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>

using namespace std;

class Sound {
public:
    Sound();
    ~Sound();
    void loadMedia();
    void playSound(int);
    void playMusic(int);
private:
    Mix_Music *Intro;
    Mix_Chunk *Landing;
    //Mix_Chunk *Running;
};

#endif