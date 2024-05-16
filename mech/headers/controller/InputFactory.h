#pragma once

#include "../entities/Entity.h"

#include <SDL.h>
#include <vector>

using std::vector;

class InputFactory{
    public:
        int *gameMode;
        SDL_Event *event;
        vector<Entity*> *entityList;
        bool processInput();
        InputFactory(SDL_Event *event, int *gameMode, vector<Entity*> *entityList);
};