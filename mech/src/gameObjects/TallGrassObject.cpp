#include "../../headers/gameObjects/TallGrassObject.h"
#include "../../headers/gameObjects/GameObjectManager.h"
#include "../../headers/TextureManager.h"
#include "../../headers/items/ItemCodes.h"
#include "../../headers/items/ToolItem.h"
#include <cstdlib>

TallGrassObject::TallGrassObject(short id, int xT, int yT, short shortGrassType) : GameObject(2,16,32){
    ID = id;
    xTile = xT;
    yTile = yT;
    objectTexture = textureManager.gameObjectsTexture; 
    renderRects.posOnTexture = {96 + shortGrassType * 16,16,16,32};
    objectHealth = 1;
}

void TallGrassObject::handleClick(Item* clickedBy){
    if(clickedBy->itemType == ItemCodes::SOULSWORD){
        if(ToolItem* tool = dynamic_cast<ToolItem*>(clickedBy)){
            objectHealth -= tool->damagePerFrame;
            if(objectHealth <= 0){
                gameObjectManager.queueObjectForRemoval(this);
                int oneInThreeChance = (int) rand() % 4;
                if(oneInThreeChance == 0){
                    GameObject::dropObject(ItemCodes::CARROTSEED,2,xTile,yTile);
                }
                else if(oneInThreeChance == 1){
                    GameObject::dropObject(ItemCodes::YUCCASEED,2,xTile,yTile);
                }else{
                    
                }
                markedForDeletion = true;
            }
        }
    }
}