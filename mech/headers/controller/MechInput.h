#pragma once
#include <SDL.h>
#include <vector>

#include "../entities/Entity.h"
class MechInput{
    public:
        bool processInput(SDL_Event *keyEvent, int *gameMode);
        MechInput();
    private:
        int processKeydown(SDL_Event *keyDownEvent, int *gameMode);
        void processMousedown(SDL_Event *mouseDownEvent);
        void processKeyup(SDL_Event *keyupEvent);
};

extern MechInput mechInput;