#pragma once
#include "Item.h"
#include <SDL.h>

class SoulSwordItem : public Item{
    public:
        SoulSwordItem(int numItems);
        SDL_Rect* getSpriteSheetPos();
    private:
        static SDL_Rect* spriteSheetPos;
};