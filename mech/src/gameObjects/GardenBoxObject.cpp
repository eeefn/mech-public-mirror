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