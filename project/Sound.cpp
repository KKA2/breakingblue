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
    loaded = 0;
}

Sound::~Sound() {
    Mix_FreeChunk(SoundEffect);
    SoundEffect = NULL;
}

void Sound::loadMedia(int load) {
    if (load != loaded) { // check if desired sound effect has been loaded
        if (load == 1) {
            Mix_FreeChunk(SoundEffect); // free previous sound effect
            SoundEffect = Mix_LoadWAV("sound/landing.wav"); // load landing sound
            loaded = 1; // track which sound effect has been loaded
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
    loadMedia(sound); // load sound effect to be played
    if (sound == 1 && Mix_Playing(1) == 0) // landing, make sure sound not already playing
        Mix_PlayChannel(1,SoundEffect,0);
    else if (sound == 2 && Mix_Playing(2) == 0) // running
        Mix_PlayChannel(2,SoundEffect,0);
    else if (sound == 3) // punching, sound can overlap
        Mix_PlayChannel(3,SoundEffect,0);
}
