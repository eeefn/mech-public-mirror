#include "../../headers/gameObjects/ShrubObject.h"
#include "../../headers/TextureManager.h"
#include "../../headers/items/ItemCodes.h"

ShrubObject::ShrubObject(short id, int xT, int yT, short shrubType) : ResourceObject(2,32,32,ItemCodes::STICK,1,ItemCodes::SOULAXE){
    objectHealth = 100;
    ID = id;
    xTile = xT;
    yTile = yT;
    objectTexture = textureManager.gameObjectsTexture; 
    renderRects.posOnTexture = {(shrubType) * 32, 32, 32, 32};
}