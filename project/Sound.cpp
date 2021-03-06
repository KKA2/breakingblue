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
            SoundEffect = Mix_LoadWAV("sound/effects/landing.wav"); // load landing sound
            loaded = 1; // track which sound effect has been loaded
        }
        else if (load == 2) {
            Mix_FreeChunk(SoundEffect);
            SoundEffect = Mix_LoadWAV("sound/effects/kicking.wav");
            loaded = 2;
        }
        else if (load == 3) {
            Mix_FreeChunk(SoundEffect);
            SoundEffect = Mix_LoadWAV("sound/effects/punching.wav");
            loaded = 3;
        }
        else if (load == 4) {
            Mix_FreeChunk(SoundEffect);
            SoundEffect = Mix_LoadWAV("sound/effects/success.wav");
            loaded = 4;
        }
        else if (load == 5) {
            Mix_FreeChunk(SoundEffect);
            SoundEffect = Mix_LoadWAV("sound/effects/failure.wav");
            loaded = 5;
        }
        else if (load == 6) {
            Mix_FreeChunk(SoundEffect);
            SoundEffect = Mix_LoadWAV("sound/effects/win.wav");
            loaded = 6;
        }
        else if (load == 7) {
            Mix_FreeChunk(SoundEffect);
            SoundEffect = Mix_LoadWAV("sound/effects/select.wav");
            loaded = 7;
        }
        else if (load == 8) {
            Mix_FreeChunk(SoundEffect);
            SoundEffect = Mix_LoadWAV("sound/effects/pageflip.wav");
            loaded = 8;
        }
    }
}

void Sound::playSound(int sound) {
    loadMedia(sound); // load sound effect to be played
    if (sound == 1 && Mix_Playing(1) == 0) // landing, make sure sound not already playing
        Mix_PlayChannel(1,SoundEffect,0);
    else if (sound == 2 && Mix_Playing(2) == 0) // kicking, no overlap
        Mix_PlayChannel(2,SoundEffect,0);
    else if (sound == 3 && Mix_Playing(3) == 0) // punching, no overlap
        Mix_PlayChannel(3,SoundEffect,0);
    else if (sound == 4) // success, play at end of each level and if win game
        Mix_PlayChannel(4,SoundEffect,0);
    else if (sound == 5) // failure, play if lose game
        Mix_PlayChannel(4,SoundEffect,0);
    else if (sound == 6) // win, play if win game
        Mix_PlayChannel(4,SoundEffect,0);
    else if (sound == 7) { // select a choice from the menu (i.e. pressed the spacebar)
        Mix_PlayChannel(5,SoundEffect,0);
        while (Mix_Playing(5) != 0); // play until complete
    }
    else if (sound == 8) // page flip, can overlap
        Mix_PlayChannel(6,SoundEffect,0);
}
