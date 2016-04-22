// Text.h
// interface for text class for displaying textual animations
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Texture.h"
#include <vector> 

#ifndef _TEXT_H_
#define _TEXT_H_

using namespace std;
class Text {

public:
	Text();
	~Text();
	void display(SDL_Rect *);
	void setUp(SDL_Window *,SDL_Renderer *);
    void loadMedia(string);
private:
	int xPos;
	int yPos;
	int chars;
	SDL_Window *Window;
    SDL_Renderer *Renderer;
    Texture text;
    vector<SDL_Rect> Chars;

};
#endif //_TEXT_H_