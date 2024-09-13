#pragma once
#include "ResourceObject.h"
#include <SDL.h>

class GardenBoxObject : public ResourceObject{
    public:
        GardenBoxObject(short id, int xT, int yT);
        bool place();
        void updateRenderTextureR();
        void updateRenderTextureL();
        void handleTextureBasedOnNeighbors();
        void handleClick(Item* clickedBy);
        void render(SDL_Renderer* rend);
    private:
        void setSeedTexRect(int seedType, short phase);
        struct SeedSlot{
            bool occupied;
            short phase;
            int seedType;
        };
        RenderRect seedRects;
        SeedSlot slotOne = {false,0,-1};
        SeedSlot slotTwo = {false,0, -1};
};
