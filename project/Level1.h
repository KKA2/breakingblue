// Level1.h
// Interface for Level1 derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _LEVEL1
#define _LEVEL1

#include "Levels.h"

using namespace std;

const int LEVEL_WIDTH = 4000;
const int LEVEL_HEIGHT = 400;

class Level1 : public Levels {
public:
    Level1();
    ~Level1();
    void loadMedia();
    void loadTexture();
private:
};

#endif