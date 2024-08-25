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
//child class tool 
//holds broken and soul color attributes
//getSpriteSheetPosition gets broken and soul color pos, it decides based on color and soul attributes