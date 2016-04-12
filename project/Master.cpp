// Breaking Blue
// Master.cpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <cmath>
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

    double maxJumpHeight = 150;

    updateCamera();
    update();

    level1.playMusic();

    int notOnGround = checkGround(&person, &level1);
    while (notOnGround) { //continue until player hits ground or edge of board
        //updateCamera();
        person.setYPos(person.getYPos() + 2); //shift player down one pixel (falling)
        notOnGround = checkGround(&person, &level1);
        update();
    }

    while (!quit) {
        while (person.getState() == 4) {
            person.setCurrRoll(person.getCurrRoll() + .5);
            if (person.getMoveDir() == SDL_FLIP_NONE)
                moveFigure(8,0);
            else
                moveFigure(-8,0);
            
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
                        person.setState(2);
                        if (person.getJumpDir() == 0)
                            person.setJumpDir(-1);
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
        //cout << person.getJumpDir()*(maxJumpHeight - ((maxJumpHeight+5)-(person.getJumpHeight()))/(maxJumpHeight+5)*50) << endl;
        double changeY =  person.getJumpDir() * ((maxJumpHeight+10 + person.getJumpHeight())/(maxJumpHeight+10)) * 50;    
        person.setJumpHeight(person.getJumpHeight() + changeY);
        moveFigure(0,changeY);
        if (person.getJumpDir() == -1) {
            person.setState(2);
            if (abs(person.getJumpHeight()) >= maxJumpHeight) {
                person.setJumpDir(1);
            }
        }
        else if (person.getJumpDir() == 1) {
            bool onGround = checkGround(&person, &level1);
            if (onGround) {
                sound.playSound(1);
                person.setState(0);
                person.setJumpDir(0);
                person.setJumpHeight(0);
                person.setYPos(person.getYPos() - changeY);
                moveFigure(0,0);
            }
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
            moveFigure(-10,0);
            if (person.getJumpHeight() == 0)
                person.setCurrRun(person.getCurrRun() + .3);
        }
        else if (state[SDL_SCANCODE_RIGHT]) { // run right
            if (person.getState() != 2)
                sound.playSound(2);
            person.setMoveDir(SDL_FLIP_NONE);
            if (person.getState() != 2)
                person.setState(1);
            moveFigure(10,0);
            if (person.getJumpHeight() == 0)
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

void Master::moveFigure(const double chX, const double chY) {
    person.setXPos(person.getXPos() + chX);
    person.setYPos(person.getYPos() + chY);

    if (person.getJumpHeight() == 0) { // not jumping
        //ensure person is on ground
        int notOnGround = checkGround(&person, &level1);
        while (notOnGround) { //continue until player hits ground or edge of board
            //updateCamera();
            //person.setState(2);
            if (notOnGround == 1) { //is in air
                person.setYPos(person.getYPos() + 2); //shift player down one pixel (falling)
                notOnGround = checkGround(&person, &level1);
            } else { //notOnGround == 2
                person.setYPos(person.getYPos() - 2); //shift player up one pixel (falling)
                notOnGround = checkGround(&person, &level1);
            }
        }

    }
    //check if person is not in foreground
    bool hasCollided = checkCollision(&person, &level1);
    
    if (person.getXPos() > LEVEL_WIDTH - 75)
        person.setXPos(LEVEL_WIDTH - 75);
    else if (person.getXPos() < 0)
        person.setXPos(0);

    if (person.getYPos() > LEVEL_HEIGHT)
        exit(1);
    else if (person.getYPos() < 0)
        person.setYPos(0);
    
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

bool Master::checkCollision(Person *person, Level1 *level) {
    //check if on ground
    int feet = person->getYPos();
    return 0;
}

int Master::checkGround(Person *person, Level1 *level1) {
    //get value of pixel at current position of player on foreground
    //Texture * currTex = level1->getForeground();

    Uint32 pixel, abovePixel;
    pixel = level1->getForeground()->getPixel(person->getXPos()+40,person->getYPos()+93);
    abovePixel = level1->getForeground()->getPixel(person->getXPos()+40,person->getYPos()+90);
    
    //convert to RGBA values
    Uint8 alpha;
    alpha = level1->getForeground()->getAlpha(pixel);

    Uint8 beta;
    beta = level1->getForeground()->getAlpha(abovePixel);    
    if(int(alpha) < 10) //transparent pixel; is in air
        return 1;
    if(int(beta) > 10) //pixel is not transparent   
        return 2;

    return 0;

}