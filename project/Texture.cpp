// Texture.cpp
// Implemation of Texture class; creates and renders textures for display
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Texture.h"

using namespace std;

Texture::Texture() {
    Renderer = NULL;
    mTexture = NULL;
    Surface = NULL;
}

Texture::~Texture() {
    // free the texture
    free();
    // free the surface
    SDL_FreeSurface(Surface);
}

void Texture::free() {
    // check if the texture exists
    if (mTexture != NULL) {
        // destroy the previous texture
        SDL_DestroyTexture(mTexture);
        // reset to null
        mTexture = NULL;
    }
}

void Texture::setUp(SDL_Renderer *renderer) {
    Renderer = renderer;
}

void Texture::loadFromFile(string path) {
    // free the previously loaded texture, if exists
    free();
    // initialize to NULL to allow for error checking
    SDL_Texture* newTexture = NULL;
    // load image
    Surface = IMG_Load(path.c_str());
    if (Surface == NULL) // error check
        printf("Unable to load image %s! SDL_image Error: %s",path.c_str(),IMG_GetError());
    else {
        // color key image
        SDL_SetColorKey(Surface,SDL_TRUE,SDL_MapRGB(Surface->format,0,0xFF,0xFF));
        // create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(Renderer,Surface); // create texture from Surface pixels
        if (newTexture == NULL)
            printf("Unable to create texture from %s! SDL Error: %s\n",path.c_str(),SDL_GetError());
        else {
            mWidth = Surface->w;
            mHeight = Surface->h;
        }
        // set the class texture as the loaded texture
        mTexture = newTexture;
    }
}
void Texture::render(int x, int y, SDL_Rect *clip, SDL_RendererFlip flip, double angle, SDL_Point *center) {
    // set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    // set clip rendering dimensions
    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    // render to screen
    SDL_RenderCopyEx(Renderer,mTexture,clip,&renderQuad,angle,center,flip);

}

Uint8 Texture::getAlpha(Uint32 pixel) {
    // initialize all necessary values to call GetRGBA
    Uint8 red,green,blue,alpha;
    // call function to find the alpha value
    SDL_GetRGBA(pixel,Surface->format,&red,&green,&blue,&alpha);
    return alpha;
}

Uint32 Texture::getPixel(int x, int y) {
    // get the format of the surface to be analyzed
    int bpp = Surface->format->BytesPerPixel;
    // make the surface read-only
    SDL_LockSurface(Surface);
    // take a sample of the specific pixel
    Uint8 *p = (Uint8 *)Surface->pixels + y * Surface->pitch + x * bpp;
    // unlock the surface
    SDL_UnlockSurface(Surface);
    // check the format and return the associated pixel vaue
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
