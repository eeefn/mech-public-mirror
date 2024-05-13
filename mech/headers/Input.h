#pragma once
#include <SDL.h>
#include <vector>

#include "../headers/Entity.h"
using std::vector;
class Input{
    public:
        int processKeydown(SDL_Event *keyEvent,vector<Entity*> *entityList);
        Input();
};

extern Input input;