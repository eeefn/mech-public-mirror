#pragma once
#include <SDL.h>
#include "../RenderRects.h"

class Item{
    public:
        Item(int numItems,int itType);
        virtual ~Item();
        RenderRectRef renderRectRefs;
        virtual SDL_Rect* getSpriteSheetPos();
        void update(float dt);
        int numberOfItems;
        int itemType;
        int xPos;
        int yPos;
        int yVel;
        int yAcc;
        int objectPlaced = -1;
};