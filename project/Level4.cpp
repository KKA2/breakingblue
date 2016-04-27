// Level4.cpp
// Implementation of Level4 derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Level4.h"

using namespace std;

Level4::Level4() {
    CurrText = 0;
}

Level4::~Level4() {
    Foreground.free();
    LevelFourText.clear();
}

void Level4::setUp(SDL_Renderer *renderer) {
    // set up renderer on all textures
    Level::setUp(renderer);
    Foreground.setUp(renderer);

    Level::setLevelWidth(1000);
    Level::setLevelHeight(400);
    Level::setCameraX(0);
    Level::setCameraY(0);

    Text tempText(49);
    Text tempText2(61);
    Text tempText3(54);

    LevelFourText.push_back(tempText);
    LevelFourText.push_back(tempText2);
    LevelFourText.push_back(tempText3);

    for(unsigned int i=0; i<LevelFourText.size();i++) {
        LevelFourText[i].setUp(renderer);   
    }
}

void Level4::display() {
    // call display of Level class
    Level::display();
    // get current camera display
    SDL_Rect cam = *Level::getCamera();
    // render foreground onto screen
    getForeground()->render(0,0,&cam);
    if(CurrText == 0) {
        for (int i = 0; i<3; i++) {
            LevelFourText[i].display(&cam, i); // display text
        }
        
    }
}

void Level4::loadMedia() {
    // set up media from Level class
    Level::setBackground("imgs/bg/lvl4.png");
    Level::setMusic(Mix_LoadMUS("sound/thunderous.wav"));
    // load all foreground textures
    Foreground.loadFromFile("imgs/lvl4/base1.png"); // PLACEHOLDER

    LevelFourText[0].loadMedia("imgs/lvl4/mission03.png");
    LevelFourText[1].loadMedia("imgs/lvl4/missionInfo1.png");
    LevelFourText[2].loadMedia("imgs/lvl4/missionInfo2.png");

}

Texture * Level4::getForeground() {
    // get foreground
    return &Foreground;
}
void Level4::setCurrText() {
    CurrText++;
}
