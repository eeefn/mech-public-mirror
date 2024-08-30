
#include "../../headers/gameObjects/RockObject.h"
#include "../../headers/gameObjects/gameObjectManager.h"
#include "../../headers/TextureManager.h"
#include "../../headers/items/ItemCodes.h"
#include "../../headers/items/ToolItem.h"
#include <memory>

#include <iostream>
RockObject::RockObject(short id, int xT, int yT, short rockType) : GameObject(2,32,32) {
    ID = id;
    xTile = xT;
    yTile = yT;
    objectTexture = textureManager.gameObjectsTexture; 
    spriteSheetPos = {rockType * 32,0,32,32};
    objectHealth = 100;
}

void RockObject::handleClick(Item* clickedBy){
    std::cout << "rock handling click with health: " << objectHealth << std::endl;
    //consider changing this to some broader item classification, ie pickaxe
    if(clickedBy->itemType == ItemCodes::SOULPICK){
        if(ToolItem* tool = dynamic_cast<ToolItem*>(clickedBy)){
            objectHealth -= tool->damagePerFrame;
            if(objectHealth <= 0){
                gameObjectManager.queueObjectForRemoval(this);
            }
        }
    }
}