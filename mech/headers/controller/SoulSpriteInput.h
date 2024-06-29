#pragma once
#include <SDL.h>


class SoulSpriteInput{
    public:
        bool processInput(SDL_Event *keyEvent, int *gameMode);
        SoulSpriteInput();
    private:
        bool soulSpriteSpawned = false;
        int processKeydown(SDL_Event *keyEvent, int *gameMode);
        void processMousedown(SDL_Event *keydownEvent);
        void processKeyup(SDL_Event *keyupEvent);
        void processHeldKeys(SDL_Event *keyEvent);
};

extern SoulSpriteInput soulSpriteInput;