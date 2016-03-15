#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "Person.h"
#include "Texture.h"

using namespace std;

Person::Person() {
    Window = NULL;
    Renderer = NULL;
}

Person::~Person() {
    RunningTexture.free();
    StandingTexture.free();
    JumpingTexture.free();
    DuckingTexture.free();
}

void Person::setUp(SDL_Window *window, SDL_Renderer *renderer) {
    Window = window;
    Renderer = renderer;

    RunningTexture.setUp(renderer);
    StandingTexture.setUp(renderer);
    JumpingTexture.setUp(renderer);
    DuckingTexture.setUp(renderer);
}

void Person::loadMedia() {
    RunningTexture.loadFromFile("running.png");
    for (int i=0;i<7;i++) {
        Running[i].x = 350*i;
        Running[i].y = 0;
        Running[i].w = 350;
        Running[i].h = 250;
    }
    StandingTexture.loadFromFile("standing.png");
    Standing.x = 0; Standing.y = 0; Standing.w = 350; Standing.h = 250;
    JumpingTexture.loadFromFile("jumping.png");
    Jumping.x = 0; Jumping.y = 0; Jumping.w = 350; Jumping.h = 250;
    DuckingTexture.loadFromFile("ducking.png");
    Ducking.x = 0; Ducking.y = 0; Ducking.w = 350; Ducking.h = 250;
}

void Person::draw(int xPos, int yPos, int currRun, int state, SDL_RendererFlip dir) {
    if (state == 0)
        StandingTexture.render(xPos,yPos,&Standing,dir);
    else if (state == 1)
        RunningTexture.render(xPos,yPos,&Running[currRun],dir);
    else if (state == 2)
        JumpingTexture.render(xPos,yPos,&Jumping,dir);
    else if (state == 3)
        DuckingTexture.render(xPos,yPos,&Ducking,dir);
}