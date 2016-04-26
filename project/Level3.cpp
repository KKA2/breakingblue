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
    LevelThreeText.clear();
}

void Level3::setUp(SDL_Renderer *renderer) {
    // set up renderer on all textures
    Level::setUp(renderer);
    Foreground.setUp(renderer);

    Level::setLevelWidth(3360);
    Level::setLevelHeight(3360);
    Level::setCameraX(1622);
    Level::setCameraY(0);

    Text tempText(29);
    Text tempText2(44);
    Text tempText3(41);

    LevelThreeText.push_back(tempText);
    LevelThreeText.push_back(tempText2);
    LevelThreeText.push_back(tempText3);

    for(unsigned int i=0; i<LevelThreeText.size();i++) {
        LevelThreeText[i].setUp(renderer);   
    }

}

void Level3::display() {
    // call display of Level class
    Level::display();
    // get current camera display
    SDL_Rect cam = *Level::getCamera();
    // render foreground onto screen
    getForeground()->render(0,0,&cam);
    // display the mission parameters
    if(CurrText == 0) {
        for (int i = 0; i<3; i++) {
            LevelThreeText[i].display(&cam, i); // display text
        }
        
    }
}

void Level3::loadMedia() {
    // set up media from Level class
    Level::setBackground("imgs/bg/lvl1.png"); // PLACEHOLDER
    Level::setMusic(Mix_LoadMUS("sound/suspense.wav"));
    // load all foreground textures
    Foreground.loadFromFile("imgs/lvl3/maze.png");

    LevelThreeText[0].loadMedia("imgs/lvl3/mission02.png");
    LevelThreeText[1].loadMedia("imgs/lvl3/intel.png");
    LevelThreeText[2].loadMedia("imgs/lvl3/purple.png");

}

Texture * Level3::getForeground() {
    // get foreground
    return &Foreground;
}

void Level3::setCurrText() {
    CurrText++; // move to next direction for mission parameter text
}