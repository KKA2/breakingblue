// Text.cpp
// Tutorial animations on screen
// Project: Breaking Blue
// Authors: Kate Barlock, Kat Herring, Ann Keenan

#include "Text.h"

using namespace std;

Text::Text() {
    CurrText = 0;
    TutorialRect.x = 0;
    TutorialRect.y = 0;
    TutorialRect.w = 450;
    TutorialRect.h = 125;
}

Text::~Text() {
    Tutorial.free();
}

void Text::setUp(SDL_Renderer *renderer) {
    Renderer = renderer;
    Tutorial.setUp(renderer);
}

void Text::loadText(string text) {
    Tutorial.loadFromFile(text); // load image
}

void Text::display() { // line to display on
    if (CurrText < TotalText) // if still have text to display
        Tutorial.render(20,20,&TutorialRect); // display at (20,20)
}

int Text::getCurrText() {
    return CurrText;
}

void Text::setCurrText(int currText) {
    CurrText = currText;
}

int Text::getTotalText() {
    return TotalText;
}

void Text::setTotalText(int totalText) {
    TotalText = totalText;
}