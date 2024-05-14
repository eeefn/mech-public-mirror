#pragma once
#include <SDL.h>
#include <vector>


#include "../headers/Entity.h"
using std::vector;

class EditInput{
    public:
        int processKeydown(SDL_Event *keydownEvent, int *xOffset, int *yOffset, int *gameMode);
        EditInput();
};

extern EditInput editInput;