// Level.cpp
// Implementation of Level class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Level.h"
#include "Master.h" // include for screen height/width

using namespace std;

Level::Level() {
    // initialize to NULL
    Renderer = NULL;
    Background = NULL;
    Music = NULL;
    // initialize size of screen to 0
    LevelWidth = 0;
    LevelHeight = 0;
    // set bounds of display to allow for side scrolling
    Camera.x = 0;
    Camera.y = 0;
    Camera.w = 1000;
    Camera.h = 400;
}

Level::~Level() {
    // free loaded images
    SDL_DestroyTexture(Background);
    Background = NULL;
    // free loaded music
    Mix_FreeMusic(Music);
    Music = NULL;
}

void Level::setUp(SDL_Renderer *renderer) {
    // allow for textures to be rendered onto the screen
    Renderer = renderer;
    Tutorial.setUp(renderer);
}

void Level::display() {
    // draw background image onto screen
    SDL_RenderCopy(Renderer,Background,NULL,NULL);
}

void Level::playMusic() {
    // play music on channel, fade in over .5 seconds
    Mix_FadeInMusic(Music,-1,500);
    // set volume of music played to 50
    Mix_VolumeMusic(50);
}

SDL_Texture * Level::loadTexture(string path) {
    SDL_Texture *newTexture = NULL; // optimized surface
    SDL_Surface *loadedSurface = IMG_Load(path.c_str()); // temporary loaded surface
    newTexture = SDL_CreateTextureFromSurface(Renderer,loadedSurface);
    SDL_FreeSurface(loadedSurface); // free temporary loaded surface
    // return the loaded texture
    return newTexture;
}

void Level::setBackground(string path) {
    Background = loadTexture(path);
}

SDL_Texture * Level::getBackground() {
    return Background;
}

void Level::setLevelWidth(int levelWidth) {
    LevelWidth = levelWidth;
}

int Level::getLevelWidth() {
    return LevelWidth;
}

void Level::setLevelHeight(int levelHeight) {
    LevelHeight = levelHeight;
}

int Level::getLevelHeight() {
    return LevelHeight;
}

void Level::setCameraX(int x) {
    Camera.x = x;
}

int Level::getCameraX() {
    return Camera.x;
}

void Level::setCameraY(int y) {
    Camera.y = y;
}

int Level::getCameraY() {
    return Camera.y;
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

int Level::getCurrText() {
    return Tutorial.getCurrText();
}

int Level::getTotalText() {
    return Tutorial.getTotalText();
}
