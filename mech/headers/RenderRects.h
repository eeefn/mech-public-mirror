#pragma once
#include <SDL.h>

struct RenderRect{
    SDL_Rect posOnTexture;
    SDL_Rect posOnScreen;
};

struct RenderRectRef{
    SDL_Rect *posOnTexture;
    SDL_Rect posOnScreen;
};