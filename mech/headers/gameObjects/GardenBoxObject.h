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
        void handleClick();
};