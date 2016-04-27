// Text.h
// interface for text class for displaying textual animations
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Texture.h"
#include <vector> 

#ifndef _TEXT
#define _TEXT

using namespace std;
class Text {

public:
	Text();
	~Text();
	void setUp(SDL_Renderer *);
    void loadText(string);
    void display(); // default to show text
    int getCurrText();
    void setCurrText(int);
    int getTotalText();
    void setTotalText(int);
private:
    SDL_Renderer *Renderer;
    Texture Tutorial; // instructions
    SDL_Rect TutorialRect;
    int CurrText; // current text box displayed
    int TotalText; // total number of text boxes
};
#endif