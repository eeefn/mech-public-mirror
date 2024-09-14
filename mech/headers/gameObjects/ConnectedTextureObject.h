#pragma once
#include <SDL.h>
#include "GameObject.h"

class ConnectedTextureObject : public virtual GameObject{
    public:
        ConnectedTextureObject(int xPosUnconnectedTex, int yPosUnconnectedTex);
        bool place();
        void handleTextureBasedOnNeighbors();
        void updateRenderTextureL();
        void updateRenderTextureR();
    private:
        SDL_Rect originalPosOnTexture;
};