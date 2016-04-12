// Levels.cpp
// Implementation of Levels Class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "Levels.h"
#include "Texture.h"
#include "Master.h"

using namespace std;

Levels::Levels() {
    Window = NULL;
    Renderer = NULL;
    Background = NULL;
    Music = NULL;
    Camera.x = 0;
    Camera.y = 0;
    Camera.w = SCREEN_WIDTH;
    Camera.h = SCREEN_HEIGHT;
}

Levels::~Levels() {
    // free loaded images
    SDL_DestroyTexture(Background);
    Background = NULL;

    Foreground.free();

    Mix_FreeMusic(Music);
    Music = NULL;
}

SDL_Texture * Levels::loadTexture(string path) {
    SDL_Texture *newTexture = NULL; // optimized surface
    SDL_Surface *loadedSurface = IMG_Load(path.c_str()); // loaded surface
    newTexture = SDL_CreateTextureFromSurface(Renderer,loadedSurface);
    SDL_FreeSurface(loadedSurface);

    return newTexture;
}

void Levels::setUp(SDL_Window *window, SDL_Renderer *renderer) {
    Window = window;
    Renderer = renderer;
    Foreground.setUp(renderer);
}

void Levels::display() {
    SDL_RenderCopy(Renderer,Background,NULL,NULL);
    Foreground.render(0,0,&Camera);
}

void Levels::playMusic() {
    Mix_PlayMusic(Music,-1);
    Mix_VolumeMusic(30);
}

void Levels::setBackground(SDL_Texture *background) {
    Background = background;
}

SDL_Texture * Levels::getBackground() {
    return Background;
}

void Levels::setForeground(string path) {
    Foreground.loadFromFile(path);
}

Texture * Levels::getForeground() {
    return &Foreground;
}

void Levels::setCameraX(int x) {
    Camera.x = x;
}

int Levels::getCameraX() {
    return Camera.x;
}

void Levels::setMusic(Mix_Music *music) {
    Music = music;
}

Mix_Music * Levels::getMusic() {
    return Music;
}

int Levels::getLevelW() {
    return lWidth;
}

void Levels::setLWidth(int width) {
    lWidth = width;
}
