// Breaking Blue
// Master.cpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "Master.h"
#include "Person.h"
#include "Sound.h"

using namespace std;

Master::Master() {
    init();
    person.setUp(Window,Renderer);
    level1.setUp(Window,Renderer);
    loadMedia();
}

Master::~Master() {
    // destroy window    
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    Window = NULL;
    Renderer = NULL;

    // quit SDL subsystems
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Master::init() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"); // set texture filtering to linear
    Window = SDL_CreateWindow("Breaking Blue", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    Renderer = SDL_CreateRenderer(Window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // create renderer for window
    SDL_SetRenderDrawColor(Renderer,0xFF,0xFF,0xFF,0xFF); // initialize renderer color
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
}

void Master::loadMedia() {
    person.loadMedia();
    level1.loadMedia();
}

void Master::play() {
    bool quit = false;
    SDL_Event e;

    double maxJumpHeight = 100;

    updateCamera();
    update();

    level1.playMusic();    

    while (!quit) {
        while (person.getState() == 4) {
            person.setCurrRoll(person.getCurrRoll() + .5);
            if (person.getMoveDir() == SDL_FLIP_NONE)
                moveFigure(8);
            else
                moveFigure(-8);
            
            if (person.getCurrRoll() < 8)
                update();
            else {
                person.setCurrRoll(0);
                person.setState(3);
            }
        }

        while (person.getState() == 5) {
            person.setCurrPunch(person.getCurrPunch() + .5);
            if (person.getCurrPunch() < 11)
                update();
            else {
                person.setCurrPunch(0);
                break;
            }
        }

        while (SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT)
                quit = true;
            else if(e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_UP: 
                        /*if (person.getState() == 1) { // if running
                            person.setState(6);
                        }
                        else {*/
                            person.setState(2);
                            if (person.getJumpDir() == 0)
                                person.setJumpDir(-1);
                        //}
                    break;
                    case SDLK_q:
                        quit = true;
                    break;
                }
            }
        }
/*
        while (person.getState() == 6) {
            person.setCurrFlip(person.getCurrFlip() + .5);
            if (person.getMoveDir() == SDL_FLIP_NONE)
                moveFigure(1);
            else
                moveFigure(-1);

            if (person.getCurrFlip() < 26)
                update();
            else {
                person.setCurrFlip(0);
                person.setState(0);
            }
        }
*/
        person.setState(0);
        person.setYPos(person.getYPos()+person.getJumpDir()*((maxJumpHeight+5)-(GroundLevel-person.getYPos()))/(maxJumpHeight+5)*50);

        if (person.getYPos() < GroundLevel) {
            person.setState(2);
            if (person.getYPos() <= GroundLevel-maxJumpHeight)
                person.setJumpDir(1);
        }
        else if (person.getJumpDir() == 1) {
            sound.playSound(1);
            person.setState(0);
            person.setJumpDir(0);
            person.setYPos(GroundLevel);
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_DOWN]) { // duck
            if (person.getState() != 2) {
                person.setState(3);
                if (state[SDL_SCANCODE_LEFT]) {
                    person.setMoveDir(SDL_FLIP_HORIZONTAL);
                    person.setState(4);
                }
                else if (state[SDL_SCANCODE_RIGHT]) {
                    person.setMoveDir(SDL_FLIP_NONE);
                    person.setState(4);
                }
            }
        }
        else if (state[SDL_SCANCODE_LEFT]) { // run left
            if (person.getState() != 2) // if not jumping
                sound.playSound(2);
            person.setMoveDir(SDL_FLIP_HORIZONTAL);
            if (person.getState() != 2)
                person.setState(1);
            moveFigure(-10);
            if (person.getYPos() >= GroundLevel)
                person.setCurrRun(person.getCurrRun() + .3);
        }
        else if (state[SDL_SCANCODE_RIGHT]) { // run right
            if (person.getState() != 2)
                sound.playSound(2);
            person.setMoveDir(SDL_FLIP_NONE);
            if (person.getState() != 2)
                person.setState(1);
            moveFigure(10);
            if (person.getYPos() >= GroundLevel)
                person.setCurrRun(person.getCurrRun() + .3);
        }
        else {
            person.setCurrRun(0);
        }

        if (person.getCurrRun() >= 7) // keep in bounds of array for running
            person.setCurrRun(0);

        update();
    }
}

void Master::moveFigure(const double chX) {
    person.setXPos(person.getXPos() + chX);

    if (person.getXPos() > LEVEL_WIDTH - 75)
        person.setXPos(LEVEL_WIDTH - 75);
    else if (person.getXPos() < 0)
        person.setXPos(0);

    updateCamera();
}

void Master::updateCamera() {
    //center camera over the player
    level1.setCameraX(person.getXPos() + 75 - SCREEN_WIDTH/2);
    //keep camera in bounds
    if (level1.getCameraX() < 0)
        level1.setCameraX(0);
    else if (level1.getCameraX() > level1.getLevelW() - SCREEN_WIDTH)
        level1.setCameraX(level1.getLevelW() - SCREEN_WIDTH);
}

void Master::update() {
    SDL_RenderClear(Renderer);
    level1.display();
    // foreground
    person.draw(level1.getCameraX());
    // update screen
    SDL_RenderPresent(Renderer);
}
