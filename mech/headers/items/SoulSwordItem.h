#pragma once
#include "ToolItem.h"
#include <SDL.h>

class SoulSwordItem : public ToolItem{
    public:
        SoulSwordItem();
        SDL_Rect* getSpriteSheetPos();
    private:
        static SDL_Rect* spriteSheetPos;
};