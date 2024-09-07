#pragma once
#include <SDL.h>
#include "Item.h"

class GardenBoxItem : public Item{
    public:
        GardenBoxItem(int numItems);
        SDL_Rect* getSpriteSheetPos();
    private:
        static SDL_Rect* spriteSheetPos;
};