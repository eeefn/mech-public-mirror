#pragma once
#include <SDL.h>
#include "Item.h"

class SoulShardItem : public Item{
    public:
        SoulShardItem(int numItems);
        SDL_Rect* getSpriteSheetPos();
        static SDL_Rect* spriteSheetPos;
};