// Level1.cpp
// Implementation of Level1 derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Level1.h"
#include "Texture.h"

using namespace std;

Level1::Level1() {
    Window = NULL;
    Renderer = NULL;
    currDoor = 1;
    currDoor1 = 0;
}

Level1::~Level1() {
    Door1Texture.free();
    Door2Texture.free();
    Door3Texture.free();
}

void Level1::setUp(SDL_Window *window, SDL_Renderer *renderer) {
    Levels::setUp(window,renderer);

    Window = window;
    Renderer = renderer;
    Door1Texture.setUp(renderer);
    Door2Texture.setUp(renderer);
    Door3Texture.setUp(renderer);
}

void Level1::display() {
    Levels::display(int(currDoor));
    if (currDoor1 < 5)
        Door1Texture.render(Door1[int(currDoor1)].x-Levels::getCameraX(),Door1[int(currDoor1)].y,Levels::getCamera());
    Door2Texture.render(0,0,Levels::getCamera());
    Door3Texture.render(0,0,Levels::getCamera());
}

void Level1::loadMedia() {
    Levels::setBackground("imgs/bg/level1.png");
    Levels::setForeground("imgs/fg/level1_base1.png",0);
    Levels::setForeground("imgs/fg/level1_base2.png",1);
    Levels::setForeground("imgs/fg/level1_base3.png",2);
    Levels::setForeground("imgs/fg/level1_base4.png",3);
    Levels::setMusic(Mix_LoadMUS("sound/intro.wav"));

    Door1Texture.loadFromFile("imgs/fg/level1_door1.png");
    for (int i=0;i<6;i++) {
        Door1[i].x = 0;
        Door1[i].y = 400*i;
        Door1[i].w = 4000;
        Door1[i].h = 400;
    }
    Door2Texture.loadFromFile("imgs/fg/level1_door2.png");
    Door3Texture.loadFromFile("imgs/fg/level1_door3.png");
}

Texture * Level1::getForeground() {
    // get foreground corresponding to whichever door has yet to be broken
    if (currDoor < 2)
        return Levels::getForeground(0);
    else if (currDoor < 3)
        return Levels::getForeground(1);
    else if (currDoor < 4)
        return Levels::getForeground(2);
    else
        return Levels::getForeground(3);
}

double Level1::getCurrDoor() {
    return currDoor;
}

void Level1::setCurrDoor(double door) {
    currDoor = door;
}

double Level1::getCurrDoor1() {
    return currDoor1;
}

void Level1::setCurrDoor1(double door) {
    currDoor1 = door;
}

int Level1::getLevelWidth() {
    return LEVEL_WIDTH;
}
