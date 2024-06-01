#pragma once
#include <SDL.h>
#include "../headers/constants.h"
#include "../headers/entities/Entity.h"
class Camera{
    public:
        int yOffset, xOffset;
        int texSelY, texSelX;
        int tilesPerWindowHeight, tilesPerWindowWidth;
        
        SDL_Rect tileSelect[TILE_WIDTH_IN_TILE_MAP][TILE_WIDTH_IN_TILE_MAP];
        SDL_Rect renTile;
        SDL_Rect objTex;
        SDL_Texture *tileTexture;
        SDL_Texture *objectTexture;
        Entity *cameraTarget;
        void renderMap(Entity *cameraTarget);
        int getXPosWithinFrame(int xPos);
        void initializeCamera(int height,int width, SDL_Renderer *renderer,SDL_Texture *tileTexture,SDL_Texture *objectTexture);
        void update(Entity *cameraTarget);
        Camera();
        SDL_Renderer *renderer;
    private:
        void textureSelect(short select);
        void initializeTileSelect();
        void updateTargetDisplayPos(Entity *cameraTarget);
        void updateCameraOffsets(Entity *cameraTarget);
};

extern Camera camera;