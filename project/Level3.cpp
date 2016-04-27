// Level3.cpp
// Implementation of Level3 derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Level3.h"
#include "Master.h" // include for screen height/width

using namespace std;

Level3::Level3() {
    // select a random maze
    CurrMaze = rand()%5;
}

Level3::~Level3() {
    // free all textures
    for (int f=0;f<5;f++)
        Foreground[f].free();
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
}

void Level3::display() {
    // call display of Level class
    Level::display();
    // get current camera display
    SDL_Rect *cam = Level::getCamera();
    // render foreground onto screen
    getForeground()->render(0,0,cam);
    // draw purple fig at end of maze
    PurpleFigTexture.render(1802-cam->x,3266-cam->y,&PurpleFig);

    Tutorial.display();
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

    Tutorial.loadText("imgs/lvl3/txt/0.png");
    Tutorial.setTotalText(1);
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

void Level3::setCurrMaze() {
    CurrMaze = rand()%5; // choose a random number between 0-4 and set as the current maze
}

void Level3::setCurrText() {
    Tutorial.setCurrText(Tutorial.getCurrText() + 1); // increment currText
}
