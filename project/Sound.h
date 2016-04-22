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
    void loadMedia(int); // load sound effect
    void playSound(int); // play sound effect
private:
    Mix_Chunk *SoundEffect; // store the currently loaded sound effect
    int loaded; // store number correlating to the currently loaded sound
};

#endif