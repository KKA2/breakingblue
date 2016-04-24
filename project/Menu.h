// Menu.h
// Interface for Menu derived class
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#ifndef _MENU
#define _MENU

#include "Level.h"
#include "Texture.h"

using namespace std;

class Menu : public Level {
public:
    Menu();
    ~Menu();
    // implement virtual functions of Level class
    void setUp(SDL_Renderer *);
    void display();
    void loadMedia();
private:
};

#endif
