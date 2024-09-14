#pragma once
#include <SDL.h>
#include "Item.h"

class YuccaRootItem: public Item{
    public:
        YuccaRootItem(int numItems);
        SDL_Rect* getSpriteSheetPos();
    private:
        static SDL_Rect* spriteSheetPos;
};
