// Breaking Blue
// Sound.cpp

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
<<<<<<< HEAD
            SoundEffect = Mix_LoadWAV("music/landing.wav");
=======
            SoundEffect = Mix_LoadWAV("./sound/landing.wav");
>>>>>>> dc68d187ea539599a94f8c6faea6c82016f2f8ce
            loaded = 1;
        }
        else if (load == 2) {
            Mix_FreeChunk(SoundEffect);
<<<<<<< HEAD
            SoundEffect = Mix_LoadWAV("music/running.wav");
=======
            SoundEffect = Mix_LoadWAV("./sound/running.wav");
>>>>>>> dc68d187ea539599a94f8c6faea6c82016f2f8ce
            loaded = 2;
        }
    }
}

void Sound::playSound(int sound) {
    loadMedia(sound);
    Mix_Volume(0,100);
    if (Mix_Playing(0) == 0)
        Mix_PlayChannel(0,SoundEffect,0);
}
