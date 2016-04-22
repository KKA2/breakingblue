// Text.cpp
// text animations on screen
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Text.h"

using namespace std;

Text::Text() { //number of characters in image to display (52 in 00)
	Window = NULL;
    Renderer = NULL;
    xPos = 0;
    yPos = 25;
    chars = 52;

}
Text::~Text() {
	text.free();
}
void Text::setUp(SDL_Window *window, SDL_Renderer *renderer) {
    Window = window;
    Renderer = renderer;

    text.setUp(renderer);
}
void Text::loadMedia(string file) {
    text.loadFromFile(file);
    SDL_Rect temp;
    for (int i=1;i<=52;i++) {
        temp.x = 0;
        temp.y = 0;
        temp.w = 10*i;
        temp.h = 25;
        Chars.push_back(temp);
    }
    return;
}
void Text::display(SDL_Rect * cam) {
    int camX = cam->x;
    text.render(xPos-camX,yPos,&Chars[51],SDL_FLIP_NONE); //does not scroll through text yet
}