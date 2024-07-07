#include <SDL.h>
#include "../../headers/constants.h"
#include "../../headers/entities/SoulSprite.h"
#include "../../headers/TextureManager.h"
#include "../../headers/Map.h"
#include "../../headers/GameObject.h"
#include <math.h>

SoulSprite::SoulSprite(Entity *entity){
    hostEntity = entity;
    posX = entity->posX;
    posY = entity->posY;
    entityWidth = 32;
    entityHeight = 32;
    entitySpeedX = 100;
    entitySpeedY = 100;
    displayRect = {entity->displayRect.x,entity->displayRect.y,32,32};
    velY = 0; velX = 0;
    accX =0; accY = 0;
    return;
}
SoulSprite::~SoulSprite(){
    return;
}

void SoulSprite::updateEntity(float dt){
	posX += round(velX * dt);
	posY += round(velY * dt);
    map.manageHighlightedObjects(&displayRect);
    return;
}

void SoulSprite::moveLeft(bool key) {
    Entity::moveLeft(key);
}

void SoulSprite::moveUp(bool key) {
    Entity::moveUp(key);
}
void SoulSprite::moveRight(bool key) {
	Entity::moveRight(key);
}
void SoulSprite::moveDown(bool key) {
	Entity::moveDown(key);
}

void SoulSprite::processCollision(bool collisions[4]){
    return;
}

void SoulSprite::render(SDL_Renderer *renderer){
    SDL_RenderCopy(renderer, textureManager.guiTexture, &this->spriteLocationOnTexture, &this->displayRect);
    return;
}