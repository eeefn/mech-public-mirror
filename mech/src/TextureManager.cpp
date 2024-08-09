#include "../headers/TextureManager.h"
#include <stdio.h>
#include <iostream>

TextureManager textureManager;

void TextureManager::initPermanentTextures(SDL_Renderer* renderer){
	initializeTexture(&this->tileTexture,"../resources/tile4.bmp",renderer);
	initializeTexture(&this->gameObjectTexture,"../resources/objSheetv1.bmp",renderer);
	initializeTexture(&this->guiTexture,"../resources/gui.bmp",renderer);
	initializeTexture(&this->mechTexture,"../resources/mech.bmp",renderer);
	initializeTexture(&this->spriteTexture,"../resources/mushBoyJ.bmp",renderer);
	initializeTexture(&this->headTexture,"../resources/headIsolated.bmp",renderer);
	initializeTexture(&this->torsoTexture,"../resources/torsoIsolated.bmp",renderer);
	initializeTexture(&this->legsTexture,"../resources/legsIsolated.bmp",renderer);
	initializeTexture(&this->mushFullTexture,"../resources/fullBodyPlayerAnims.bmp",renderer);
	initializeTexture(&this->caveBackroundTexture,"../resources/caveBackround.bmp",renderer);
	initializeTexture(&this->portalTexture,"../resources/portal.bmp",renderer);
	initializeTexture(&this->gameObjectsTexture,"../resources/objectSheet.bmp",renderer);
	initializeTexture(&this->inventoryTexture,"../resources/Inventory.bmp",renderer);
	initializeTexture(&this->itemsTexture,"../resources/ItemSheet.bmp",renderer);
	initializeTexture(&this->numberTexture,"../resources/Numbers.bmp",renderer);
}

/*Double pointer because passing uninitialized values seems to cause xPlosion*/
void TextureManager::initializeTexture(SDL_Texture** textureToInit, const char* filePath,SDL_Renderer* renderer){
	SDL_Surface* surfaceFromBMP = SDL_LoadBMP(filePath);
	if (!surfaceFromBMP) { fprintf(stderr, "could not find %s",filePath); }
	*textureToInit = SDL_CreateTextureFromSurface(renderer,surfaceFromBMP);
	SDL_FreeSurface(surfaceFromBMP);
}
