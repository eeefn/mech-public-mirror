#pragma once
#include <vector>
#include "items/Item.h"
#include "gameObjects/BuildShadow.h"

using std::vector;

class Hotbar{ 
    public:
        static int hotbarScale;
        Hotbar(vector<Item*> *bar);
        void render();
        void update();
        void setSelectedSlot(int setTo);
        Item* getItemAtSelectedSlot();
        void incrementSelectedSlot();
        void decrementSelectedSlot();
        void handleClick(int mouseXPos,int mouseYPos,int buttonPressed);
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
        BuildShadow buildShadow;
        void initializeHotbar();
        int getItemXPos(int xInvenPos);
        int slots;
        int selectedSlot = 0;
};