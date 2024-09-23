#pragma once
#include <SDL.h>
#include <vector>

#include "../entities/Entity.h"
using std::vector;

class PlayInput{
    public:
        bool processInput(SDL_Event *keyEvent, int *gameMode);
        void update();
        PlayInput();
    private:
        int processKeydown(SDL_Event *keyEvent, int *gameMode);
        void processMousedown(SDL_Event *keydownEvent);
        void processKeyup(SDL_Event *keyupEvent);
        void processHeldKeys(SDL_Event *keyEvent);
        void processScrollWheel(SDL_Event *wheelEvent);
        void processHeldClick();
        bool mousedown = false;
};

extern PlayInput playInput;