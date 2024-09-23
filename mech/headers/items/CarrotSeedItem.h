#pragma once
#include <SDL.h>
#include "Item.h"

class CarrotSeedItem : public Item{
    public:
        CarrotSeedItem(int numItems);
        SDL_Rect* getSpriteSheetPos();
    private:
        static SDL_Rect* spriteSheetPos;
};