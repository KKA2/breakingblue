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
    // select a random maze
    CurrMaze = rand()%5;
}

Level3::~Level3() {
    // free all textures
    for (int f=0;f<5;f++)
        Foreground[f].free();
    LevelThreeText.clear();
    PurpleFigTexture.free();
}

void Level3::setUp(SDL_Renderer *renderer) {
    // set up renderer on all textures
    Level::setUp(renderer);
    for (int f=0;f<5;f++)
        Foreground[f].setUp(renderer);
    PurpleFigTexture.setUp(renderer);

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
    SDL_Rect *cam = Level::getCamera();
    // render foreground onto screen
    getForeground()->render(0,0,cam);
    // display the mission parameters
    if(CurrText == 0) {
        for (int i = 0; i<3; i++) {
            LevelThreeText[i].display(cam, i); // display text
        }
    }
    // draw purple fig at end of maze
    PurpleFigTexture.render(1802-cam->x,3266-cam->y,&PurpleFig);
}

void Level3::loadMedia() {
    // set up media from Level class
    Level::setBackground("imgs/bg/lvl3.png");
    Level::setMusic(Mix_LoadMUS("sound/suspense.wav"));
    // load all foreground textures
    Foreground[0].loadFromFile("imgs/lvl3/maze0.png");
    Foreground[1].loadFromFile("imgs/lvl3/maze1.png");
    Foreground[2].loadFromFile("imgs/lvl3/maze2.png");
    Foreground[3].loadFromFile("imgs/lvl3/maze3.png");
    Foreground[4].loadFromFile("imgs/lvl3/maze4.png");

    PurpleFigTexture.loadFromFile("imgs/figs/purple/ducking.png");
    PurpleFig.x = 0; PurpleFig.y = 0; PurpleFig.w = 75; PurpleFig.h = 94;

    LevelThreeText[0].loadMedia("imgs/lvl3/mission02.png");
    LevelThreeText[1].loadMedia("imgs/lvl3/intel.png");
    LevelThreeText[2].loadMedia("imgs/lvl3/purple.png");
}

Texture * Level3::getForeground() {
    if (CurrMaze == 0)
        return &Foreground[0];
    else if (CurrMaze == 1)
        return &Foreground[1];
    else if (CurrMaze == 2)
        return &Foreground[2];
    else if (CurrMaze == 3)
        return &Foreground[3];
    else
        return &Foreground[4];
}

void Level3::setCurrText() {
    CurrText++; // move to next direction for mission parameter text
}

void Level3::setCurrMaze() {
    CurrMaze = rand()%5; // choose a random number between 0-4 and set as the current maze
}