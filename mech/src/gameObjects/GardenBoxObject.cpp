#include "../../headers/gameObjects/GardenBoxObject.h"
#include "../../headers/TextureManager.h"
#include "../../headers/gameObjects/ResourceObject.h"
#include "../../headers/items/ItemCodes.h"
#include "../../headers/gameObjects/GameObjectManager.h"

GardenBoxObject::GardenBoxObject(short id, int xT, int yT) : ResourceObject(2,32,32,ItemCodes::GARDENBOX,1,ItemCodes::SOULAXE) {
    ID = id;
    xTile = xT;
    yTile = yT;
    objectTexture = textureManager.gameObjectsTexture; 
    renderRects.posOnTexture = {0,64,32,32};
    objectHealth = 50;
}

void GardenBoxObject::handleClick(Item* clickedBy){
    ResourceObject::handleClick(clickedBy);
    if(clickedBy->itemType == ItemCodes::CARROTSEED){
        if(!slotOne.occupied){
            slotOne = {true, 1, ItemCodes::CARROTSEED};
        }
        else if(!slotTwo.occupied) {
            slotTwo = {true,0,ItemCodes::CARROTSEED};
        }
    }
    else if(clickedBy->itemType == ItemCodes::YUCCASEED){
        if(!slotOne.occupied && !slotTwo.occupied){
           slotOne = {true,0,ItemCodes::YUCCASEED}; 
           slotTwo = {true,0,ItemCodes::YUCCASEED};
        }
    }
}

void GardenBoxObject::render(SDL_Renderer* rend){
    GameObject::render(rend);
    if(slotOne.occupied){
        setSeedTexRect(slotOne.seedType, slotOne.phase);
        seedRects.posOnScreen = renderRects.posOnScreen;
        SDL_RenderCopy(rend,textureManager.gameObjectsTexture,&seedRects.posOnTexture,&seedRects.posOnScreen);
    }
    if(slotTwo.occupied && slotOne.seedType != ItemCodes::YUCCASEED){
        setSeedTexRect(slotTwo.seedType,slotTwo.phase);
        seedRects.posOnScreen = renderRects.posOnScreen;
        seedRects.posOnScreen.x += 2 * 16; 
        SDL_RenderCopy(rend,textureManager.gameObjectsTexture,&seedRects.posOnTexture,&seedRects.posOnScreen);
    }
}

void GardenBoxObject::setSeedTexRect(int seedType, short phase){
    int yOffset = 96 + ((seedType - 8) * 32);
    int xOffset = phase * 32;
    seedRects.posOnTexture = {xOffset,yOffset,32,32};
}

bool GardenBoxObject::place(){
    hasLeftNeighbor = gameObjectManager.checkForLeftNeighbor(this);
    hasRightNeighbor = gameObjectManager.checkForRightNeighbor(this);
    handleTextureBasedOnNeighbors();
    return true;
}

void GardenBoxObject::updateRenderTextureR(){
    hasLeftNeighbor = true;
    hasRightNeighbor = gameObjectManager.checkForRightNeighbor(this);
    handleTextureBasedOnNeighbors();
}

void GardenBoxObject::updateRenderTextureL(){
    hasRightNeighbor = true;
    hasLeftNeighbor = gameObjectManager.checkForLeftNeighbor(this);
    handleTextureBasedOnNeighbors();
}

void GardenBoxObject::handleTextureBasedOnNeighbors(){
    if(hasLeftNeighbor && hasRightNeighbor){
        renderRects.posOnTexture = {64,64,32,32};
    }
    else if(hasLeftNeighbor){
        renderRects.posOnTexture = {96,64,32,32};
    }
    else if(hasRightNeighbor){
        renderRects.posOnTexture = {32,64,32,32};
    }
    else{
        renderRects.posOnTexture = {0,64,32,32};
    }
}