#pragma once
#include <SDL.h>

class Item{
    public:
        Item();
        virtual ~Item();
        SDL_Rect itemPos;
        virtual SDL_Rect* getSpriteSheetPos();
};