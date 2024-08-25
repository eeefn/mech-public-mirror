#pragma once
#include "ToolItem.h"
#include <SDL.h>

class SoulPickaxeItem : public ToolItem{
    public:
        SoulPickaxeItem();
        SDL_Rect* getSpriteSheetPos();
    private:
        static SDL_Rect* spriteSheetPos;
};