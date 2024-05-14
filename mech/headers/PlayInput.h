#pragma once
#include <SDL.h>
#include <vector>

#include "../headers/Entity.h"
using std::vector;

class PlayInput{
    public:
        bool processInput(SDL_Event *keyEvent, vector<Entity*> *entityList, SDL_Rect *spriteDest,int *gameMode);
        int processKeydown(SDL_Event *keyEvent,vector<Entity*> *entityList, SDL_Rect *spriteDest, int *gameMode);
        void processMousedown(SDL_Event *keydownEvent, vector<Entity*> *entityList);
        void processKeyup(SDL_Event *keyupEvent, vector<Entity*> *entityList);
        PlayInput();
};

extern PlayInput playInput;