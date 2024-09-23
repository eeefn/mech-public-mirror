#pragma once
#include <SDL.h>
#include "Item.h"

class StickItem : public Item{
    public:
        StickItem(int numItems);
        SDL_Rect* getSpriteSheetPos();
    private:
        static SDL_Rect* spriteSheetPos;
};