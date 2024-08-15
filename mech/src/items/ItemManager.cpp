#include "../../headers/items/ItemManager.h"
#include "../../headers/Collider.h"
#include "../../headers/WindowManager.h"
#include "../../headers/TextureManager.h"
#include "../../headers/Camera.h"
#include <iostream>
#include <SDL.h>

ItemManager itemManager;

ItemManager::ItemManager(){
    return;
}

void ItemManager::makeExternalItem(int itemCode, int itemCount, int xPos, int yPos){
    Item* newItem = itemFactory.makeItem(itemCode,itemCount);
    newItem->itemPos = {0,0,16*itemFactory.itemScale,16*itemFactory.itemScale};
    newItem->xPos = xPos;
    newItem->yPos = yPos;
    itemList.push_back(newItem);
    return; 
}

void ItemManager::updateItems(float dt){
    for(auto item : itemList){
        item->update(dt);
        if(collider.checkItemCollision(item)){
            item->yPos = (item->yPos) / mapInfo.TILE_DIM * mapInfo.TILE_DIM;
        }
        item->itemPos.x = camera.getXPosWithinFrame(item->xPos);
        item->itemPos.y = camera.getYPosWithinFrame(item->yPos);
    }
    return; 
}

void ItemManager::renderItems(){
    for(auto item : itemList){
       SDL_RenderCopy(windowManager.renderer,textureManager.itemsTexture,item->getSpriteSheetPos(),&item->itemPos);
    }
    return;
}

void ItemManager::checkItemCollisions(){
    return; 
}
