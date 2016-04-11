// Breaking Blue
// Levels.cpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "Levels.h"
#include "Texture.h"

using namespace std;

Levels::Levels() {
    Window = NULL;
    Renderer = NULL;
    Background = NULL;
    Foreground = NULL;
    Music = NULL;
}

Levels::~Levels() {
    // free loaded images
    SDL_DestroyTexture(Background);
    Background = NULL;

    SDL_DestroyTexture(Foreground);
    Foreground = NULL;

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
}

void Levels::display(SDL_Rect * camera) {
    SDL_RenderCopy(Renderer,Background,NULL,NULL);
    SDL_RenderCopy(Renderer,Foreground, camera, NULL);
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
void Levels::setMusic(Mix_Music *music) {
    Music = music;
}
Mix_Music * Levels::getMusic() {
    return Music;
}
void Levels::setForeground(SDL_Texture *foreground) {
    Foreground = foreground;
}
SDL_Texture * Levels::getForeground() {
    return Foreground;
}
int Levels::getLevelW() {
    return lWidth;
}
SDL_Renderer * Levels::getRenderer() {
    return Renderer;
}
void Levels::setLWidth(int width) {
    lWidth = width;
}