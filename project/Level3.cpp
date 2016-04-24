// Level3.cpp
// Implementation of Level3 derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Level3.h"
#include "Master.h" // include for screen height/width

using namespace std;

Level3::Level3() {
    // initialize to 0
    CurrText = 0;
}

Level3::~Level3() {
    // free all textures
    Foreground.free();
}

void Level3::setUp(SDL_Renderer *renderer) {
    // set up renderer on all textures
    Level::setUp(renderer);
    Foreground.setUp(renderer);
    MissionParam.setUp(renderer);

    Level::setLevelWidth(1000);
    Level::setLevelHeight(4000);
    Level::setCameraX(0);
    Level::setCameraY(Level::getLevelHeight()-SCREEN_HEIGHT);
}

void Level3::display() {
    // call display of Level class
    Level::display();
    // get current camera display
    SDL_Rect cam = *Level::getCamera();
    // render foreground onto screen
    getForeground()->render(0,0,&cam);
    // display the mission parameters
    if(CurrText == 1) {
        MissionParam.display(&cam, 0); // PLACEHOLDER
    }
}

void Level3::loadMedia() {
    // set up media from Level class
    Level::setBackground("imgs/bg/lvl1.png"); // PLACEHOLDER
    Level::setMusic(Mix_LoadMUS("sound/suspense.wav"));
    // load all foreground textures
    Foreground.loadFromFile("imgs/lvl3/base1.png");

    MissionParam.loadMedia("imgs/lvl1/text/missionParam.png"); // PLACEHOLDER
}

Texture * Level3::getForeground() {
    // get foreground
    return &Foreground;
}

void Level3::setCurrText() {
    CurrText++; // move to next direction for mission parameter text
}