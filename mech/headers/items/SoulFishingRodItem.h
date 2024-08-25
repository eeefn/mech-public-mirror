#pragma once
#include "ToolItem.h"
#include <SDL.h>

class SoulFishingRodItem : public ToolItem{
    public:
        SoulFishingRodItem();
        SDL_Rect* getSpriteSheetPos();
    private:
        static SDL_Rect* spriteSheetPos;
};