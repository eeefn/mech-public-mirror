#include "../../headers/gameObjects/ResourceObject.h"
#include "../../headers/items/ToolItem.h"
#include "../../headers/items/Item.h"
#include "../../headers/gameObjects/GameObjectManager.h"

ResourceObject::ResourceObject(int itemCode, int numDropped, int brokenBy){
    droppedResourceItemCode = itemCode;
    numResourceDropped = numDropped;
    toolBrokenBy = brokenBy;
}

void ResourceObject::handleClick(Item* clickedBy){
    //consider changing this to some broader item classification, ie pickaxe
    if(clickedBy->itemType == toolBrokenBy){
        if(ToolItem* tool = dynamic_cast<ToolItem*>(clickedBy)){
            objectHealth -= tool->damagePerFrame;
            if(objectHealth <= 0){
                gameObjectManager.queueObjectForRemoval(this);
                GameObject::dropObject(droppedResourceItemCode,numResourceDropped,xTile,yTile);
                markedForDeletion = true;
            }
        }
    }
}