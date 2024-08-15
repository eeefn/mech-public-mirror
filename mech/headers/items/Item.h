#pragma once
#include <SDL.h>

class Item{
    public:
        Item(int numItems,int itType);
        virtual ~Item();
        SDL_Rect itemPos;
        virtual SDL_Rect* getSpriteSheetPos();
        void update(float dt);
        int numberOfItems;
        int itemType;
        int xPos;
        int yPos;
        int yVel;
        int yAcc;
};