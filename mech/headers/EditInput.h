#pragma once
#include <SDL.h>
#include <vector>


#include "../headers/Entity.h"
using std::vector;

class EditInput{
    public:
        int processKeydown(SDL_Event *keydownEvent, SDL_Rect *selWindowRen,int *xOffset,int *yOffset,short *selectColor, int *gameMode);
        EditInput();
};

extern EditInput editInput;