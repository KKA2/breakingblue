#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "Sound.h"

using namespace std;

Sound::Sound() {
    Intro = NULL;
    Landing = NULL;
    //Running = NULL;
}

Sound::~Sound() {
    Mix_FreeChunk(Landing);
    //Mix_FreeChunk(Running);
    Landing = NULL;
    //Running = NULL;

    Mix_FreeMusic(Intro);
    Intro = NULL;
}

void Sound::loadMedia() {
    Intro = Mix_LoadMUS("intro.wav");
    Landing = Mix_LoadWAV("landing.wav");
    //Running = Mix_LoadWAV("running.wav");
}

void Sound::playSound(int sound) {
    Mix_Volume(0,100);
    if (sound == 1) // jump landing
        Mix_PlayChannel(0,Landing,0);
    else if (sound == 2) // running
        if (Mix_Playing(0) == 0)
            Mix_PlayChannel(0,Landing,0);
}

void Sound::playMusic(int sound) {
    if (sound == 1) {
        Mix_PlayMusic(Intro,-1);
        Mix_VolumeMusic(30);
    }
}