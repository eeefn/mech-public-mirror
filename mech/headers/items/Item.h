#pragma once
#include <SDL.h>

class Item{
    public:
        Item(int numItems);
        virtual ~Item();
        SDL_Rect itemPos;
        virtual SDL_Rect* getSpriteSheetPos();
        int numberOfItems;
};