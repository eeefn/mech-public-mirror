#pragma once
#include <SDL.h>
#include "../headers/constants.h"
class Camera{
    public:
        int yOffset;
        int xOffset;
        int texSelY;
        int texSelX;
        int tilesPerWindowHeight;
        int tilesPerWindowWidth;
        SDL_Rect tileSelect[TILE_WIDTH_IN_TILE_MAP][TILE_WIDTH_IN_TILE_MAP];
        SDL_Rect renTile;
        SDL_Rect objTex;
        SDL_Texture *tileTexture;
        SDL_Texture *objectTexture;
        void renderMap();
        void textureSelect(short select);
        void initializeTileSelect();
        void initializeCamera(int height,int width, SDL_Renderer *renderer,SDL_Texture *tileTexture,SDL_Texture *objectTexture);
        Camera();
        SDL_Renderer *renderer;
};

extern Camera camera;