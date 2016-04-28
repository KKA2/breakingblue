// Outro.cpp
// Implementation of Outro derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Outro.h"

using namespace std;

Outro::Outro() {
    CurrFade = 0;
    CurrScene = 0;
}

Outro::~Outro() {
    // free all textures
    for (int f=0;f<11;f++)
        Fade[f].free();
    for (int s=0;s<4;s++)
        Scene[s].free();
}

void Outro::setUp(SDL_Renderer *renderer) {
    Renderer = renderer;
    for (int f=0;f<11;f++)
        Fade[f].setUp(renderer);
    for (int s=0;s<4;s++)
        Scene[s].setUp(renderer);
}

void Outro::loadMedia() {
    Level::setMusic(Mix_LoadMUS("sound/hiphop.wav"));

    Fade[0].loadFromFile("imgs/fade/0.png");
    Fade[1].loadFromFile("imgs/fade/10.png");
    Fade[2].loadFromFile("imgs/fade/20.png");
    Fade[3].loadFromFile("imgs/fade/30.png");
    Fade[4].loadFromFile("imgs/fade/40.png");
    Fade[5].loadFromFile("imgs/fade/50.png");
    Fade[6].loadFromFile("imgs/fade/60.png");
    Fade[7].loadFromFile("imgs/fade/70.png");
    Fade[8].loadFromFile("imgs/fade/80.png");
    Fade[9].loadFromFile("imgs/fade/90.png");
    Fade[10].loadFromFile("imgs/fade/100.png");

    Scene[0].loadFromFile("imgs/bg/outro0.png");
    Scene[1].loadFromFile("imgs/bg/outro1.png");
    Scene[2].loadFromFile("imgs/bg/outro2.png");
    Scene[3].loadFromFile("imgs/bg/outro3.png");
}

void Outro::display() {
    SDL_RenderClear(Renderer); // clear screen
    SDL_Rect *cam = Level::getCamera();
    Scene[CurrScene].render(0,0,cam); // current scene
    Fade[CurrFade].render(0,0,cam); // current fade
    SDL_RenderPresent(Renderer); // update screen
}

void Outro::animate() {
    Level::playMusic();
    SDL_Delay(200);

    CurrScene = 0; // first scene
    show();
    SDL_Delay(100);
    hide();
    SDL_Delay(100);

    CurrScene = 1; // next scene
    show();
    SDL_Delay(100);
    hide();
    SDL_Delay(400);

    CurrScene = 2;
    show();
    SDL_Delay(1800);
    hide();
    SDL_Delay(1600);

    CurrScene = 3;
    show();
    SDL_Delay(1800);
    hide();
    SDL_Delay(1600);
}

void Outro::show() {
    for (int f=10;f>=0;f--) { // increase opacity (to show scene from black screen)
        CurrFade = f;
        display();
        SDL_Delay(100); // wait a tenth of a second
    }
}

void Outro::hide() {
for (int f=0;f<11;f++) { // decrease opacity (to hide scene)
        CurrFade = f;
        display();
        SDL_Delay(100); // wait a tenth of a second
    }
}