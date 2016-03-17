#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <cmath>
#include "Master.h"

using namespace std;

int main() {
    Master master;

    bool quit = false;
    SDL_Event e;

    double groundLevel = SCREEN_HEIGHT-250;
    double maxJumpHeight = 250;
    double jumpDirection = 0;

    double xPos=SCREEN_WIDTH/2, yPos=groundLevel;

    bool isRunning = false;
    double currRun=0;
    SDL_RendererFlip moveDirection = SDL_FLIP_NONE;
    int personState = 0; // 0=standing, 1=running, 2=jumping

    master.update((int)xPos,(int)yPos,(int)currRun,personState,moveDirection);

    master.playMusic(1);

    while (!quit) {
        personState = 0; // assume standing position

        while (SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT)
                quit = true;
            else if(e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_SPACE: personState = 2; if (jumpDirection == 0) jumpDirection=-1; break;
                    case SDLK_q: quit = true; break;
                }
            }
        }
        yPos+=jumpDirection*((maxJumpHeight+5)-(groundLevel-yPos))/(maxJumpHeight+5)*50;

        if (yPos < groundLevel) {
            personState = 2;
            if (yPos <= groundLevel-maxJumpHeight)
                jumpDirection = 1;
        }
        else { // end jump
            if (jumpDirection == 1)
                master.playSound(1);
            jumpDirection = 0;
            personState = 0;
            yPos = groundLevel;
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_DOWN]) {
            if (personState != 2)
                personState = 3;
        }
        else {
            if (state[SDL_SCANCODE_LEFT]) {
                if (personState != 2) // if not jumping
                    master.playSound(2);
                moveDirection = SDL_FLIP_HORIZONTAL;
                if (personState != 2)
                    personState = 1;
                if (xPos > -100)
                    xPos-=10;
                if (yPos >= groundLevel)
                    currRun+=.3;
            }
            if (state[SDL_SCANCODE_RIGHT]) {
                if (personState != 2)
                    master.playSound(2);
                moveDirection = SDL_FLIP_NONE;
                if (personState != 2)
                    personState = 1;
                if (xPos < (SCREEN_WIDTH-250))
                    xPos+=10;
                if (yPos >= groundLevel)
                    currRun+=.3;
            }
        }

        if (personState == 0)
            currRun = 0;

        if (currRun >= 7) // keep in bounds of array for running
            currRun = 0;

        master.update((int)xPos,(int)yPos,(int)currRun,personState,moveDirection);
    }
    return 0;
}
