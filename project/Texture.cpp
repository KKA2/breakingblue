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
    mTexture = NULL;
}

Texture::~Texture() {
    free();
}

void Texture::setUp(SDL_Renderer *renderer) {
    Renderer = renderer;
}

void Texture::loadFromFile(string path) {
    free();
    IMG_Init(IMG_INIT_PNG); //adds PNG support
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str()); // load image
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s", path.c_str(), IMG_GetError() );
    } else {
        //color key image
        SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,0,0xFF,0xFF));
        
        //create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(Renderer,loadedSurface); // create texture from surface pixels
        if(newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        
        SDL_FreeSurface(loadedSurface); // get rid of old loaded surface
        mTexture = newTexture;
    }
}

void Texture::free() {
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
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
int Texture::getWidth() {
    return mWidth;
}
int Texture::getHeight() {
    return mHeight;
}