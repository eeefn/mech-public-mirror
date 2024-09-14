#pragma once
#include <SDL.h>
#include "Item.h"

class CarrotItem: public Item{
    public:
        CarrotItem(int numItems);
        SDL_Rect* getSpriteSheetPos();
    private:
        static SDL_Rect* spriteSheetPos;
};