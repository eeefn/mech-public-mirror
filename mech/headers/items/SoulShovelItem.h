
#pragma once
#include "ToolItem.h"
#include <SDL.h>

class SoulShovelItem : public ToolItem{
    public:
        SoulShovelItem();
        SDL_Rect* getSpriteSheetPos();
    private:
        static SDL_Rect* spriteSheetPos;
};