#include "../../headers/gameObjects/GardenBoxObject.h"
#include "../../headers/TextureManager.h"
#include "../../headers/gameObjects/ResourceObject.h"
#include "../../headers/items/ItemCodes.h"

GardenBoxObject::GardenBoxObject(short id, int xT, int yT) : ResourceObject(2,32,32,ItemCodes::GARDENBOX,1,ItemCodes::SOULAXE) {
    ID = id;
    xTile = xT;
    yTile = yT;
    objectTexture = textureManager.gameObjectsTexture; 
    renderRects.posOnTexture = {0,64,32,32};
    objectHealth = 50;
}