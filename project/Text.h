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
	Text(int num);
	~Text();
	void display(SDL_Rect *);
	void setUp(SDL_Renderer *);
    void loadMedia(string);
private:
    Texture text;
    vector<SDL_Rect> Chars;
	int XPos;
	int YPos;
	int NumChars;
};
#endif