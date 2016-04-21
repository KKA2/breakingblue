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

    void free();
    void setUp(SDL_Renderer *);
    SDL_Texture * loadTexture(string);
    void loadFromFile(string);
    void loadFromRenderedText(string);
    void render(int,int,SDL_Rect *,SDL_RendererFlip = SDL_FLIP_NONE,double = 0.0,SDL_Point * = NULL);

    Uint8 getAlpha(Uint32);
    Uint32 getPixel(int,int);

    int getWidth();
    int getHeight();
private:
    SDL_Renderer *Renderer;
    SDL_Texture *mTexture;
    SDL_Surface *surface;
    int mWidth;
    int mHeight;
};

#endif