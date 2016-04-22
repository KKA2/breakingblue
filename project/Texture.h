// Texture.h
// Interface for Texture class; creates and renders textures for display
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _TEXTURE
#define _TEXTURE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>

using namespace std;

class Texture {
public:
    Texture();
    ~Texture();
    // utility functions
    void free(); // destroy texture to free space
    void setUp(SDL_Renderer *); // set Renderer
    void loadFromFile(string); // load texture image from a specified path
    void render(int,int,SDL_Rect *,SDL_RendererFlip = SDL_FLIP_NONE,double = 0.0,SDL_Point * = NULL);
    // get values from the texture
    Uint8 getAlpha(Uint32); // get alpha value of a specific pixel
    Uint32 getPixel(int,int); // get pixel of a specific location
    // get functions
    int getWidth();
    int getHeight();
private:
    SDL_Renderer *Renderer;
    SDL_Surface *Surface;
    SDL_Texture *mTexture;
    int mWidth;
    int mHeight;
};

#endif