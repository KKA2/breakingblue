// Sound.h
// Interface for Sound Class; sound effects
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

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
    void loadMedia(int);
    void playSound(int);
private:
    Mix_Chunk *SoundEffect;
    int loaded;
};

#endif