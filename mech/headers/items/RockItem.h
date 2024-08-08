#pragma once
#include <SDL.h>
#include "Item.h"

class RockItem : public Item{
    public:
        RockItem(int numItems);
        SDL_Rect* getSpriteSheetPos();
    private:
        static SDL_Rect* spriteSheetPos;
};