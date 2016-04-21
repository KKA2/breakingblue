// Texture.cpp
// Implemation of Texture class; creates and renders textures for display
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Texture.h"

using namespace std;

Texture::Texture() {
    Renderer = NULL;
    mTexture = NULL;
    surface = NULL;
    gFont = NULL;
    //textColor = { 0, 0, 0 };
}

Texture::~Texture() {
    free();
    SDL_FreeSurface(surface);
}

void Texture::free() {
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
    }
}

void Texture::setUp(SDL_Renderer *renderer) {
    Renderer = renderer;
}

void Texture::loadFromFile(string path) {
    free();
    IMG_Init(IMG_INIT_PNG); // adds PNG support
    SDL_Texture* newTexture = NULL;
    surface = IMG_Load(path.c_str()); // load image
    if (surface == NULL)
        printf("Unable to load image %s! SDL_image Error: %s",path.c_str(),IMG_GetError());
    else {
        // color key image
        SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,0,0xFF,0xFF));
        
        // create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(Renderer,surface); // create texture from surface pixels
        if (newTexture == NULL)
            printf("Unable to create texture from %s! SDL Error: %s\n",path.c_str(),SDL_GetError());
        else {
            mWidth = surface->w;
            mHeight = surface->h;
        }
        
        mTexture = newTexture;
    }
}
void Texture::loadFromRenderedText(string texText) {
    //set font from file and size
    gFont = TTF_OpenFont("./clacon.ttf", 16);
    if(gFont == NULL) {
        cout << "Failed to load font! Error: " << TTF_GetError() << endl;

    } else {
        //render text
        //textColor = { 57, 255, 20 }; //Neon green
        //remove prexisting texture
        free();

        //render text surface
        surface = TTF_RenderText_Solid(gFont, texText.c_str(), textColor);
        if (surface == NULL) {
            cout << "Unable to render text surface! Error: " << TTF_GetError() << endl;
        } else {
            //create texture from surface pixels
            mTexture = SDL_CreateTextureFromSurface(Renderer, surface);

            mWidth = surface->w;
            mHeight = surface->h;
        }
    
    }
    SDL_FreeSurface(surface); //get rid of old surface
    
}
void Texture::render(int x, int y, SDL_Rect *clip, SDL_RendererFlip flip, double angle, SDL_Point *center) {
    SDL_Rect renderQuad = { x, y, mWidth, mHeight }; // set rendering space and render to screen
    if (clip != NULL) { // set clip rendering dimensions
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    // render to screen
    SDL_RenderCopyEx(Renderer,mTexture,clip,&renderQuad,angle,center,flip);
}

Uint8 Texture::getAlpha(Uint32 pixel) {
    Uint8 red,green,blue,alpha;
    SDL_GetRGBA(pixel,surface->format,&red,&green,&blue,&alpha);
    return alpha;
}

Uint32 Texture::getPixel(int x, int y) {
    int bpp = surface->format->BytesPerPixel;

    SDL_LockSurface(surface);
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    SDL_UnlockSurface(surface);

    switch (bpp) {
        case 1:
            return *p;
        break;
        case 2:
            return *(Uint16 *)p;
        break;
        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
        break;
        case 4:
            return *(Uint32 *)p;
        break;
        default:
            return 0; // avoid warnings
    }
}

int Texture::getWidth() {
    return mWidth;
}

int Texture::getHeight() {
    return mHeight;
}