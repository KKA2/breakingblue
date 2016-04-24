// Level1.cpp
// Implementation of Level1 derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Level1.h"

using namespace std;

Level1::Level1() {
    // initialize to 0
    CurrDoor = 0;
    CurrDoor1 = 0;
    CurrDoor2 = 0;
    CurrDoor3 = 0;
    CurrText = 0;
}

Level1::~Level1() {
    // free all textures
    for (int f=0;f<4;f++)
        Foreground[f].free();
    Door1Texture.free();
    Door2Texture.free();
    Door3Texture.free();
    LevelOneText.clear();
}

void Level1::setUp(SDL_Renderer *renderer) {
    // set up renderer on all textures
    Level::setUp(renderer);
    for (int f=0;f<4;f++)
        Foreground[f].setUp(renderer);
    Door1Texture.setUp(renderer);
    Door2Texture.setUp(renderer);
    Door3Texture.setUp(renderer);

    //used to create objects
    Text tempText;
    Text temp4(64);
    Text temp5(62);
    Text tempText2(22);
    Text temp3(31);
    Text temp6(42);

    //add text displays to (in order of display)
    LevelOneText.push_back(tempText);
    LevelOneText.push_back(temp4);
    LevelOneText.push_back(temp5);
    LevelOneText.push_back(tempText2);
    LevelOneText.push_back(temp3);
    LevelOneText.push_back(temp6);


    for(unsigned int i=0; i<LevelOneText.size();i++) {
        LevelOneText[i].setUp(renderer);   
    }

    Level::setLevelWidth(4000);
    Level::setLevelHeight(400);
    Level::setCameraX(0);
    Level::setCameraY(0);
}

void Level1::display() {
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
    // display the mission parameters
    if (CurrText == 0) {
        LevelOneText[0].display(&cam,0);
        LevelOneText[1].display(&cam,1);
        LevelOneText[2].display(&cam,2);
        LevelOneText[3].display(&cam,3);
    }
    else if (CurrText == 1) {
        LevelOneText[4].display(&cam,0);
    }
    else if (CurrText == 2) {
        LevelOneText[5].display(&cam,0);
    }
}

void Level1::loadMedia() {
    // set up media from Level class
    Level::setBackground("imgs/bg/lvl1.png");
    Level::setMusic(Mix_LoadMUS("sound/mysterious.wav"));
    // load mission parameters texture

    //load images for text display
    LevelOneText[0].loadMedia("imgs/lvl1/text/missionParam.png"); // image file
    LevelOneText[1].loadMedia("imgs/lvl1/text/intro1.png");
    LevelOneText[2].loadMedia("imgs/lvl1/text/intro2.png");
    LevelOneText[3].loadMedia("imgs/lvl1/text/pressC.png");
    LevelOneText[4].loadMedia("imgs/lvl1/text/howToMove.png");
    LevelOneText[5].loadMedia("imgs/lvl1/text/howToPunch.png");
    
    // load all foreground textures
    Foreground[0].loadFromFile("imgs/lvl1/base1.png");
    Foreground[1].loadFromFile("imgs/lvl1/base2.png");
    Foreground[2].loadFromFile("imgs/lvl1/base3.png");
    Foreground[3].loadFromFile("imgs/lvl1/base4.png");
    // load all door textures
    Door1Texture.loadFromFile("imgs/lvl1/door1.png");
    Door2Texture.loadFromFile("imgs/lvl1/door2.png");
    Door3Texture.loadFromFile("imgs/lvl1/door3.png");
}

Texture * Level1::getForeground() {
    // get foreground corresponding to whichever door has yet to be broken
    if (CurrDoor < 1) // no doors knocked down
        return &Foreground[0];
    else if (CurrDoor < 2)
        return &Foreground[1];
    else if (CurrDoor < 3)
        return &Foreground[2];
    else // all doors knocked down
        return &Foreground[3];
}

double Level1::getCurrDoor(int door) {
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

void Level1::setCurrDoor(int door, double currDoor) {
    if (door == 0)
        CurrDoor = currDoor;
    else if (door == 1)
        CurrDoor1 = currDoor;
    else if (door == 2)
        CurrDoor2 = currDoor;
    else if (door == 3)
        CurrDoor3 = currDoor;
}

void Level1::setCurrText() {
    CurrText++; // move to next direction for mission parameter text
}