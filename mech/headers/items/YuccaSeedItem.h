#pragma once
#include <SDL.h>
#include "Item.h"

class YuccaSeedItem : public Item{
    public:
        YuccaSeedItem(int numItems);
        SDL_Rect* getSpriteSheetPos();
    private:
        static SDL_Rect* spriteSheetPos;
};