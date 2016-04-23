// Text.cpp
// text animations on screen
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Text.h"

using namespace std;

Text::Text() {
    // position to display
    XPos = 0;
    YPos = 25;

    NumChars = 49;
}
Text::Text(int num) {
    // position to display
    XPos = 0;
    YPos = 25;
    // number of characters in image to display (49 in 00)
    NumChars = num;
}
Text::~Text() {
	text.free();
}
void Text::setUp(SDL_Renderer *renderer) {
    text.setUp(renderer);
}
void Text::loadMedia(string file) {
    text.loadFromFile(file);
    SDL_Rect temp;
    for (int i=1;i<=NumChars;i++) {
        temp.x = 0;
        temp.y = 0;
        temp.w = 11*i;
        temp.h = 26;
        Chars.push_back(temp);
    }
    return;
}
void Text::display(SDL_Rect * cam) {
    int camX = cam->x;
    static bool first = true; // display animation when first loading
    if (first) {
        for(int i=0;i<NumChars-1;i++) {
            SDL_RenderPresent(text.getRenderer());
            text.render(XPos-camX,YPos,&Chars[i],SDL_FLIP_NONE);
            
        }
        first = false;
    }
    else
        text.render(XPos-camX,YPos,&Chars[NumChars-1],SDL_FLIP_NONE); // does not scroll through text yet
}