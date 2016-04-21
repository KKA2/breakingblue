// Levels.cpp
// Implementation of Levels class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Levels.h"
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

    for (int f=0;f<4;f++)
        Foreground[f].free();

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
    for (int f=0;f<4;f++)
        Foreground[f].setUp(renderer);
}

void Levels::display(int f) {
    SDL_RenderCopy(Renderer,Background,NULL,NULL);
    Foreground[f].render(0,0,&Camera);
}

void Levels::playMusic() {
    Mix_PlayMusic(Music,-1);
    Mix_VolumeMusic(30);
}

void Levels::setBackground(string path) {
    Background = loadTexture(path);
}

SDL_Texture * Levels::getBackground() {
    return Background;
}

void Levels::setForeground(string path,int f) {
    Foreground[f].loadFromFile(path);
}

Texture * Levels::getForeground(int f) {
    return &Foreground[f];
}

void Levels::setCameraX(int x) {
    Camera.x = x;
}

int Levels::getCameraX() {
    return Camera.x;
}

SDL_Rect * Levels::getCamera() {
    return &Camera;
}

void Levels::setMusic(Mix_Music *music) {
    Music = music;
}

Mix_Music * Levels::getMusic() {
    return Music;
}
