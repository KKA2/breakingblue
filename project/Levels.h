// Breaking Blue
// Levels.h

#ifndef _LEVELS
#define _LEVELS

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>

using namespace std;

class Levels {
public:
    Levels();
    ~Levels();
    SDL_Texture * loadTexture(string);
    void setUp(SDL_Window *,SDL_Renderer *);
    void display();
    void playMusic();
    void setBackground(SDL_Texture *);
    SDL_Texture * getBackground();
    void setMusic(Mix_Music *);
    Mix_Music * getMusic();
    virtual void loadMedia() = 0;
    void setForeground(SDL_Texture *);
    SDL_Texture * getForeground();

private:
    SDL_Window *Window; // window rendering to
    SDL_Renderer *Renderer; // window renderer

    SDL_Texture *Foreground;
    SDL_Texture *Background;
    Mix_Music *Music;
};

#endif