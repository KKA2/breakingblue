// Intro.cpp
// Implementation of introduction
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Intro.h"

using namespace std;

Intro::Intro() {
    CurrScene = 0;
}

Intro::~Intro() {
    // free all textures
    for (int f=0;f<22;f++)
        Foreground[f].free();
}

void Intro::setUp(SDL_Renderer *renderer) {
    Renderer = renderer;
    for (int f=0;f<22;f++)
        Foreground[f].setUp(renderer);
}

void Intro::loadMedia() {
    // set up media from Level class
    Level::setMusic(Mix_LoadMUS("sound/melancholy.wav")); // music for menu screen

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

    Foreground[17].loadFromFile("imgs/intro/5-0.png");
    Foreground[18].loadFromFile("imgs/intro/5-1.png");
    Foreground[19].loadFromFile("imgs/intro/5-2.png");
    Foreground[20].loadFromFile("imgs/intro/5-3.png");
    Foreground[21].loadFromFile("imgs/intro/5-4.png");
}

void Intro::display() {    
    SDL_Rect cam = *Level::getCamera(); // get rect to display
    for (int i=CurrScene;i<CurrScene+NumScenes;i++) { // run through all scenes for the screen
        for(int j=CurrScene;j<=i;j++) // render screens between first and current screen
            Foreground[j].render(0,0,&cam);
        SDL_RenderPresent(Renderer); // update
        SDL_Delay(1200); // wait
    }
    CurrScene += NumScenes; // set new current scene
}

void Intro::animate() {
    Level::playMusic();
    SDL_RenderClear(Renderer);

    CurrScene = 0; // set first scene to zero

    // first screen
    NumScenes = 4;
    display();

    // second screen
    NumScenes = 5;
    display();

    // third screen
    NumScenes = 4;
    display();

    // fourth screen
    NumScenes = 4;
    display();

    // fifth screen
    NumScenes = 5;
    display();
}