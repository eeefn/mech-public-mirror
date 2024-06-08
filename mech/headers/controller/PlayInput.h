#pragma once
#include <SDL.h>
#include <vector>

#include "../entities/Entity.h"
using std::vector;

class PlayInput{
    public:
        bool processInput(SDL_Event *keyEvent, int *gameMode);
        int processKeydown(SDL_Event *keyEvent, int *gameMode);
        void processMousedown(SDL_Event *keydownEvent);
        void processKeyup(SDL_Event *keyupEvent);
        PlayInput();
};

extern PlayInput playInput;