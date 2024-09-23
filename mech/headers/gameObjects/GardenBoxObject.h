#pragma once
#include "ResourceObject.h"
#include "ConnectedTextureObject.h"
#include <chrono>
#include <SDL.h>

class GardenBoxObject : public ResourceObject, public ConnectedTextureObject{
    public:
        GardenBoxObject(short id, int xT, int yT,short scale, int width, int height);
        void handleClick(Item* clickedBy);
        void render(SDL_Renderer* rend);
        void update();
    private:
        void setSeedTexRect(int seedType, short phase);
        struct SeedSlot{
            bool occupied;
            short phase;
            int seedType;
            std::chrono::steady_clock::time_point phaseGrowthStart; 
        };
        void updateSeedSlot(SeedSlot& slot);
        bool plantSeedInSlot(SeedSlot& slot, Item* seedClickedBy);
        void dropSlotsHeldItem(SeedSlot& slot); 
        bool allSlotsOccupiedBySingleSeed = false;
        RenderRect seedRects;
        SeedSlot slotOne = {false,0,-1};
        SeedSlot slotTwo = {false,0, -1};
};
