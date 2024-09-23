#pragma once
#include <SDL.h>
#include "Item.h"

class YuccaLeafItem: public Item{
    public:
        YuccaLeafItem(int numItems);
        SDL_Rect* getSpriteSheetPos();
    private:
        static SDL_Rect* spriteSheetPos;
};