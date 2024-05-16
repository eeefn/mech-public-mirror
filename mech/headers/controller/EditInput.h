#pragma once
#include <SDL.h>
#include <vector>

#include "../entities/Entity.h"

using std::vector;

class EditInput{
    public:
        bool processInput(SDL_Event *keydownEvent, int *gameMode);
        int processKeydown(SDL_Event *keydownEvent, int *gameMode);
        EditInput();
};

extern EditInput editInput;