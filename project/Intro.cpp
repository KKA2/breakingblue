// Intro.cpp
// Implementation of introduction
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Intro.h"

using namespace std;

Intro::Intro() {

}

Intro::~Intro() {
    for (int f=0;f<17;f++)
        Foreground[f].free();
}

void Intro::setUp(SDL_Renderer *renderer) {
    Renderer = renderer;
    // set up renderer on all textures
    Level::setUp(renderer);
    for (int f=0;f<17;f++)
        Foreground[f].setUp(renderer);
    // set to fit screen
    Level::setLevelWidth(1000);
    Level::setLevelHeight(400);
    Level::setCameraX(0);
    Level::setCameraY(0);
}

void Intro::display() {
    Level::display();

    SDL_Rect cam = *Level::getCamera();
    // draw foreground for first screen
    for (int i = 0; i<4; i++) {
        for(int j = 0; j<=i; j++) {
            Foreground[j].render(0,0,&cam);          
        }
        SDL_RenderPresent(Renderer);
        SDL_Delay(800);  
    }
    SDL_RenderClear(Renderer);
    //second screen
    for (int i = 4; i<9; i++) {
        for(int j = 4; j<=i;j++) {
            Foreground[j].render(0,0,&cam);
        }
        SDL_RenderPresent(Renderer);
        SDL_Delay(800);  
    }
    //third screen
    SDL_RenderClear(Renderer);
    for (int i = 9; i<13; i++) {
        for(int j = 9; j<=i;j++) {
            Foreground[j].render(0,0,&cam);
        }
        SDL_RenderPresent(Renderer);
        SDL_Delay(800);  
    }
    SDL_RenderClear(Renderer);
    for (int i = 13; i<17; i++) {
        for(int j = 13; j<=i;j++) {
            Foreground[j].render(0,0,&cam);
        }
        SDL_RenderPresent(Renderer);
        SDL_Delay(800);  
    }

    //SDL_RenderPresent(Renderer); // update screen
}

void Intro::loadMedia() {
    // set up media from Level class
    Level::setBackground("imgs/bg/1-0.png");
    Level::setMusic(Mix_LoadMUS("sound/techno.wav")); // music for menu screen

    // load all foreground textures
    Foreground[0].loadFromFile("imgs/intro/1-0.png");
    Foreground[1].loadFromFile("imgs/intro/1-1.png");
    Foreground[2].loadFromFile("imgs/intro/1-2.png");
    Foreground[3].loadFromFile("imgs/intro/1-3.png");
    Foreground[4].loadFromFile("imgs/intro/2-0.png");
    Foreground[5].loadFromFile("imgs/intro/2-1.png");
    Foreground[6].loadFromFile("imgs/intro/2-2.png");
    Foreground[7].loadFromFile("imgs/intro/2-3.png");
    Foreground[8].loadFromFile("imgs/intro/2-4.png");
    Foreground[9].loadFromFile("imgs/intro/3-0.png");
    Foreground[10].loadFromFile("imgs/intro/3-1.png");
    Foreground[11].loadFromFile("imgs/intro/3-2.png");
    Foreground[12].loadFromFile("imgs/intro/3-3.png");
    Foreground[13].loadFromFile("imgs/intro/4-0.png");
    Foreground[14].loadFromFile("imgs/intro/4-1.png");
    Foreground[15].loadFromFile("imgs/intro/4-2.png");
    Foreground[16].loadFromFile("imgs/intro/4-3.png");
}