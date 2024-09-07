#pragma once
#include "ToolItem.h"
#include <SDL.h>
class SoulAxeItem : public ToolItem{
    public:
        SoulAxeItem();
        SDL_Rect* getSpriteSheetPos();
    private:
        static SDL_Rect* spriteSheetPos;
};