#pragma once
#include <SDL.h>
#include <vector>

#include "../Entity.h"
using std::vector;

class PlayInput{
    public:
        bool processInput(SDL_Event *keyEvent, vector<Entity*> *entityList, int *gameMode);
        int processKeydown(SDL_Event *keyEvent,vector<Entity*> *entityList, int *gameMode);
        void processMousedown(SDL_Event *keydownEvent, vector<Entity*> *entityList);
        void processKeyup(SDL_Event *keyupEvent, vector<Entity*> *entityList);
        PlayInput();
};

extern PlayInput playInput;