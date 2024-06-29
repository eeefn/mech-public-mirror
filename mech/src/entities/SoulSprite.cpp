#include <SDL.h>
#include "../../headers/constants.h"
#include "../../headers/entities/SoulSprite.h"
#include "../../headers/TextureManager.h"
#include <math.h>
SoulSprite::SoulSprite(Entity *entity){
    posX = entity->posX;
    posY = entity->posY;
    entityWidth = 32;
    entityHeight = 32;
    entitySpeedX = 100;
    this->displayRect.x = entity->displayRect.x;
    this->displayRect.y = entity->displayRect.y;
    this->displayRect.w = 32;
    this->displayRect.h = 32; 
    velY = 0; velX = 0;
    accX =0; accY = 0;
    return;
}


void SoulSprite::updateEntity(float dt){
	posX += round(velX * dt);
	posY += round(velY * dt);
    return;
}

void SoulSprite::moveLeft(bool key) {
	if (key) {
		velX -= entitySpeedX;
	}
	else {
		velX += entitySpeedX;
	}
}

void SoulSprite::moveRight(bool key) {
	if (key) {
		velX += entitySpeedX;
	}
	else {
		velX -= entitySpeedX;
	}
}

void SoulSprite::processCollision(bool collisions[4]){
    return;
}

void SoulSprite::render(SDL_Renderer *renderer){
    SDL_RenderCopy(renderer, textureManager.guiTexture, &this->spriteLocationOnTexture, &this->displayRect);
    return;
}