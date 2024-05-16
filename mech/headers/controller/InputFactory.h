#pragma once

#include "../Entity.h"

#include <SDL.h>
#include <vector>

using std::vector;

class InputFactory{
    public:
        int *gameMode;
        int *xOffset;
        int *yOffset;
        SDL_Event *event;
        vector<Entity*> *entityList;
        bool processInput();
        InputFactory(SDL_Event *event, int *xOffset, int *yOffset, int *gameMode, vector<Entity*> *entityList);
};