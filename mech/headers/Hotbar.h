#pragma once
#include <vector>
#include "items/Item.h"
using std::vector;

class Hotbar{ 
    public:
        static int hotbarScale;
        Hotbar(vector<Item*> *bar);
        void render();
        void setSelectedSlot(int setTo);
        void incrementSelectedSlot();
        void decrementSelectedSlot();
    private:
        SDL_Rect hotbarTexSelTop = {0,0,198,4};
        SDL_Rect hotbarTexSelMid = {0,9,198,19};
        SDL_Rect hotbarTexSelBottom = {0,71,198,4};
        SDL_Rect hotbarPosTop;
        SDL_Rect hotbarPosMid;
        SDL_Rect hotbarPosBottom;
        SDL_Rect itemPos;
        SDL_Rect selectPos;
        SDL_Rect selectRectTexSel = {198,0,18,18};
        vector<Item*> *barRef;
        Item *selectedItem;
        void initializeHotbar();
        int getItemXPos(int xInvenPos);
        int slots;
        int selectedSlot = 0;
};