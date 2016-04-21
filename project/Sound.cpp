// Sound.cpp
// Implemation of Sound Class; sound effects
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "Sound.h"

using namespace std;

Sound::Sound() {
    SoundEffect = NULL;
}

Sound::~Sound() {
    Mix_FreeChunk(SoundEffect);
    SoundEffect = NULL;
}

void Sound::loadMedia(int load) {
    if (load != loaded) {
        if (load == 1) {
            Mix_FreeChunk(SoundEffect);
            SoundEffect = Mix_LoadWAV("sound/landing.wav");
            loaded = 1;
        }
        else if (load == 2) {
            Mix_FreeChunk(SoundEffect);
            SoundEffect = Mix_LoadWAV("sound/running.wav");
            loaded = 2;
        }
        else if (load == 3) {
            Mix_FreeChunk(SoundEffect);
            SoundEffect = Mix_LoadWAV("sound/punching.wav");
            loaded = 3;
        }
    }
}

void Sound::playSound(int sound) {
    loadMedia(sound);
    Mix_Volume(0,100);
    if (sound == 1 && Mix_Playing(1) == 0)
        Mix_PlayChannel(1,SoundEffect,0);
    else if (sound == 2 && Mix_Playing(2) == 0)
        Mix_PlayChannel(2,SoundEffect,0);
    else if (sound == 3)
        Mix_PlayChannel(3,SoundEffect,0);
}
