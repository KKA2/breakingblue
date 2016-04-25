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
    first = true;
    NumChars = 50;
}
Text::Text(int num) {
    // position to display
    XPos = 0;
    YPos = 25;
    first = true;
    // number of characters in image to display (49 in 00)
    NumChars = num;
}
Text::~Text() {
	text.free();
    Chars.clear();
}
void Text::setUp(SDL_Renderer *renderer) {
    Renderer = renderer;
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
bool Text::display(SDL_Rect * cam, int line) { //line to display on
    //int camX = cam->x;
    //static bool first = true; // display animation when first loading
    static int i;

    if (i < NumChars) {
        text.render(XPos,YPos+26*line,&Chars[int(i)],SDL_FLIP_NONE);
        //SDL_RenderPresent(Renderer);
        i++;
        return false; //not fully displayed
    } else
        text.render(XPos,YPos+26*line,&Chars[NumChars-1],SDL_FLIP_NONE); // does not scroll through text yet
        return true; //fully displayed
}