#include <memory>

#include "../../headers/gameObjects/RockObject.h"
#include "../../headers/gameObjects/gameObjectManager.h"
#include "../../headers/TextureManager.h"
#include "../../headers/items/ItemCodes.h"
#include "../../headers/items/ToolItem.h"

RockObject::RockObject(short id, int xT, int yT, short rockType) : ResourceObject(2,32,32,ItemCodes::ROCK,1,ItemCodes::SOULPICK) {
    ID = id;
    xTile = xT;
    yTile = yT;
    objectTexture = textureManager.gameObjectsTexture; 
    renderRects.posOnTexture = {rockType * 32,0,32,32};
    objectHealth = 100;
}