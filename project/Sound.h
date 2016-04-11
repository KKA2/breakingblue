// Breaking Blue
// Sound.h

#ifndef _SOUND
#define _SOUND

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>

using namespace std;

class Sound {
public:
    Sound();
    ~Sound();
    void loadMedia(int);
    void playSound(int);
private:
    Mix_Chunk *SoundEffect;
    int loadedSound;
};

#endif