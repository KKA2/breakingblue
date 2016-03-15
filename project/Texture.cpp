#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "Texture.h"

using namespace std;

Texture::Texture() {
    Renderer = NULL;
}

Texture::~Texture() {
    free();
}

void Texture::setUp(SDL_Renderer *renderer) {
    Renderer = renderer;
}

void Texture::loadFromFile(string path) {
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str()); // load image
    SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,0,0xFF,0xFF));
    newTexture = SDL_CreateTextureFromSurface(Renderer,loadedSurface); // create texture from surface pixels
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;
    SDL_FreeSurface(loadedSurface); // get rid of old loaded surface
    mTexture = newTexture;
}

void Texture::free() {
    if(mTexture != NULL) { // free texture if it exists
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void Texture::render(int x, int y, SDL_Rect *clip, SDL_RendererFlip flip, double angle, SDL_Point *center) {
    SDL_Rect renderQuad = { x, y, mWidth, mHeight }; // set rendering space and render to screen
    if(clip != NULL) { // set clip rendering dimensions
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    // render to screen
    SDL_RenderCopyEx(Renderer,mTexture,clip,&renderQuad,angle,center,flip);
}

int Texture::getWidth() const {
    return mWidth;
}

int Texture::getHeight() const {
    return mHeight;
}