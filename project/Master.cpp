#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "Master.h"
#include "Person.h"
#include "Sound.h"

using namespace std;

Master::Master() {
    init();
    person.setUp(Window,Renderer);
    loadMedia();
}

Master::~Master() {
    // free loaded images
    SDL_DestroyTexture(Background);
    Background = NULL;

    // destroy window    
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    Window = NULL;
    Renderer = NULL;

    // quit SDL subsystems
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Master::init() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"); // set texture filtering to linear
    Window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    Renderer = SDL_CreateRenderer(Window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // create renderer for window
    SDL_SetRenderDrawColor(Renderer,0xFF,0xFF,0xFF,0xFF); // initialize renderer color
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
}

void Master::loadMedia() {
    Background = loadTexture("background.png");
    person.loadMedia();
    sound.loadMedia();
}

SDL_Texture * Master::loadTexture(string path) {
    SDL_Texture *newTexture = NULL; // optimized surface
    SDL_Surface *loadedSurface = IMG_Load(path.c_str()); // loaded surface
    newTexture = SDL_CreateTextureFromSurface(Renderer,loadedSurface);
    SDL_FreeSurface(loadedSurface);

    return newTexture;
}

void Master::update(int xPos, int yPos, int currRun, int state, SDL_RendererFlip dir) {
    SDL_RenderClear(Renderer);
    // background
    SDL_RenderCopy(Renderer,Background,NULL,NULL);
    // foreground
    person.draw(xPos,yPos,currRun,state,dir);

    SDL_RenderPresent(Renderer); // update screen
}

void Master::playSound(int s) {
    sound.playSound(s);
}
void Master::playMusic(int s) {
    sound.playMusic(s);
}