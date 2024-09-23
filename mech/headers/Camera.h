#pragma once
#include <SDL.h>
#include "../headers/constants.h"
#include "../headers/entities/Entity.h"

class Camera{
    public:
        int yOffset, xOffset;
        SDL_Rect tileSelect[mapInfo.TILE_WIDTH_IN_TILE_MAP][mapInfo.TILE_WIDTH_IN_TILE_MAP];
        
        Entity *cameraTarget;
        void renderMap();
        void renderBackround();

        int getXPosWithinFrame(int xPos);
        int getYPosWithinFrame(int yPos);
        int getGlobalXPosFromFrame(int xPos);
        int getGlobalYPosFromFrame(int yPos);
        void snapPointToTileMap(SDL_Point* pointToSnap);
        void initializeCamera(int height,int width,Entity* initialCameraTarget, SDL_DisplayMode dm);
        void update();
        void setCameraTarget(Entity *newCameraTarget);
        Camera();
    private:
        SDL_Rect* getTextureOfTile(short texType);
        void updateFrame();
        void updateCameraOffsets();
        void initializeTileSelect();
        SDL_Rect frame;
        SDL_Rect renderTile{0,0,mapInfo.TILE_DIM,mapInfo.TILE_DIM};
};

extern Camera camera;