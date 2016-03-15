// Ann Keenan
// Feb 29

#ifndef _PERSON
#define _PERSON

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "Texture.h"

using namespace std;

class Person {
public:
    Person();
    ~Person();
    void setUp(SDL_Window *,SDL_Renderer *);
    void loadMedia();
    void draw(int,int,int,int,SDL_RendererFlip);
private:
    SDL_Window *Window;
    SDL_Renderer *Renderer;

    SDL_Rect Running[7];
    Texture RunningTexture;
    SDL_Rect Standing;
    Texture StandingTexture;
    SDL_Rect Jumping;
    Texture JumpingTexture;
    SDL_Rect Ducking;
    Texture DuckingTexture;
};

#endif