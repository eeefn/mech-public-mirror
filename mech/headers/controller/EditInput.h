#pragma once
#include <SDL.h>
#include <vector>

#include "../Entity.h"

using std::vector;

class EditInput{
    public:
        bool processInput(SDL_Event *keydownEvent, int *xOffset, int *yOffset, int *gameMode);
        int processKeydown(SDL_Event *keydownEvent, int *xOffset, int *yOffset, int *gameMode);
        EditInput();
};

extern EditInput editInput;