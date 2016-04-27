// Level2.cpp
// Implementation of Level2 derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Level2.h"

using namespace std;

Level2::Level2() {
    // initialize to 0
    CurrDoor = 0;
    CurrDoor1 = 0;
    CurrDoor2 = 0;
    CurrDoor3 = 0;
}

Level2::~Level2() {
    for (int f=0;f<4;f++)
        Foreground[f].free();
    Door1Texture.free();
    Door2Texture.free();
    Door3Texture.free();
}

void Level2::setUp(SDL_Renderer *renderer) {
    // set up renderer on all textures
    Level::setUp(renderer);
    for (int f=0;f<4;f++)
        Foreground[f].setUp(renderer);
    Door1Texture.setUp(renderer);
    Door2Texture.setUp(renderer);
    Door3Texture.setUp(renderer);

    Level::setLevelWidth(2000);
    Level::setLevelHeight(800);
    Level::setCameraX(0);
    Level::setCameraY(0);
}

void Level2::display() {
    // call display of Level class
    Level::display();
    // get current camera display
    SDL_Rect cam = *Level::getCamera();
    // render foreground onto screen
    getForeground()->render(0,0,&cam);
    // adjust door animation to render based on y value of the camera
    cam.y = 400*int(CurrDoor1);
    Door1Texture.render(0,0,&cam);
    cam.y = 400*int(CurrDoor2);
    Door2Texture.render(0,0,&cam);
    cam.y = 400*int(CurrDoor3);
    Door3Texture.render(0,0,&cam);
}

void Level2::display(bool showText) {
    display(); // call other display function
    if (!showText) // mission text only
        Tutorial.setTotalText(1);
    Tutorial.display();
}

void Level2::loadMedia() {
    // set up media from Level class
    Level::setBackground("imgs/bg/lvl2.png");
    Level::setMusic(Mix_LoadMUS("sound/electronic.wav"));
    // load all foreground textures
    Foreground[0].loadFromFile("imgs/lvl2/base1.png");
    Foreground[1].loadFromFile("imgs/lvl2/base2.png");
    Foreground[2].loadFromFile("imgs/lvl2/base3.png");
    Foreground[3].loadFromFile("imgs/lvl2/base4.png");
    // load all door textures
    Door1Texture.loadFromFile("imgs/lvl2/door1.png");
    Door2Texture.loadFromFile("imgs/lvl2/door2.png");
    Door3Texture.loadFromFile("imgs/lvl2/door3.png");
    // call parent class functions
    Tutorial.loadText("imgs/lvl2/txt/0.png");
    Tutorial.setTotalText(4);
}

Texture * Level2::getForeground() {
    if (CurrDoor < 1) // no doors knocked down
        return &Foreground[0];
    else if (CurrDoor < 2)
        return &Foreground[1];
    else if (CurrDoor < 3)
        return &Foreground[2];
    else // all doors knocked down
        return &Foreground[3];
}

double Level2::getCurrDoor(int door) {
    // get CurrDoor variable associated to door
    if (door == 0)
        return CurrDoor;
    else if (door == 1)
        return CurrDoor1;
    else if (door == 2)
        return CurrDoor2;
    else
        return CurrDoor3;
}

void Level2::setCurrDoor(int door, double currDoor) {
    if (door == 0)
        CurrDoor = currDoor;
    else if (door == 1)
        CurrDoor1 = currDoor;
    else if (door == 2)
        CurrDoor2 = currDoor;
    else if (door == 3)
        CurrDoor3 = currDoor;
}


void Level2::setCurrText(int currText) {
    // load the next texture to display
    if (Tutorial.getCurrText() == 0)
        Tutorial.loadText("imgs/lvl2/txt/1.png");
    else if (Tutorial.getCurrText() == 1)
        Tutorial.loadText("imgs/lvl2/txt/2.png");
    else if (Tutorial.getCurrText() == 2)
        Tutorial.loadText("imgs/lvl2/txt/3.png");

    Tutorial.setCurrText(currText);
}
