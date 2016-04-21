// Level.cpp
// Implementation of Level class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Level.h"
#include "Master.h"

using namespace std;

Level::Level() {
    Window = NULL;
    Renderer = NULL;
    Background = NULL;
    Music = NULL;
    Camera.x = 0;
    Camera.y = 0;
    Camera.w = SCREEN_WIDTH;
    Camera.h = SCREEN_HEIGHT;
}

Level::~Level() {
    // free loaded images
    SDL_DestroyTexture(Background);
    Background = NULL;

    Mix_FreeMusic(Music);
    Music = NULL;
}

SDL_Texture * Level::loadTexture(string path) {
    SDL_Texture *newTexture = NULL; // optimized surface
    SDL_Surface *loadedSurface = IMG_Load(path.c_str()); // loaded surface
    newTexture = SDL_CreateTextureFromSurface(Renderer,loadedSurface);
    SDL_FreeSurface(loadedSurface);

    return newTexture;
}

void Level::setUp(SDL_Window *window, SDL_Renderer *renderer) {
    Window = window;
    Renderer = renderer;
}

void Level::display(int f) {
    SDL_RenderCopy(Renderer,Background,NULL,NULL);
}

void Level::playMusic() {
    Mix_PlayMusic(Music,-1);
    Mix_VolumeMusic(30);
}

void Level::setBackground(string path) {
    Background = loadTexture(path);
}

SDL_Texture * Level::getBackground() {
    return Background;
}

void Level::setCameraX(int x) {
    Camera.x = x;
}

int Level::getCameraX() {
    return Camera.x;
}

SDL_Rect * Level::getCamera() {
    return &Camera;
}

void Level::setMusic(Mix_Music *music) {
    Music = music;
}

Mix_Music * Level::getMusic() {
    return Music;
}
Texture  Level::getText() {
    return text;
}
void Level::setText(string inText) {
    text.loadFromRenderedText(inText);

}
