#pragma once


#include <SDL.h>
#include <vector>

using std::vector;

class InputFactory{
    public:
        int *gameMode;
        SDL_Event *event;
        bool processInput();
        InputFactory(SDL_Event *event, int *gameMode);
};