#pragma once
#include "../constants.h"
#include "./Entity.h"
#include <SDL.h>


class SoulSprite : public Entity{
    public:
        SDL_Rect spriteLocationOnTexture = {0, 0, 16, 16};
        SoulSprite(Entity *entity);
        void updateEntity(float dt);
        void processCollision(bool collisions[4]);
        void moveLeft(bool key);
        void moveRight(bool key);
        void render(SDL_Renderer *renderer);
};