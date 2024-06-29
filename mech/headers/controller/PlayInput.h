#pragma once
#include <SDL.h>
#include <vector>

#include "../entities/Entity.h"
using std::vector;

class PlayInput{
    public:
        bool processInput(SDL_Event *keyEvent, int *gameMode);
        PlayInput();
    private:
        int processKeydown(SDL_Event *keyEvent, int *gameMode);
        void processMousedown(SDL_Event *keydownEvent);
        void processKeyup(SDL_Event *keyupEvent);
        void processHeldKeys(SDL_Event *keyEvent);
};

extern PlayInput playInput;