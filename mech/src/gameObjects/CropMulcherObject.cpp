#include "../../headers/gameObjects/CropMulcherObject.h"
#include "../../headers/TextureManager.h"
#include "../../headers/items/ItemCodes.h"


CropMulcherObject::CropMulcherObject(short id, int xT, int yT) : GameObject(2,64,32){
    ID = id;
    xTile = xT;
    yTile = yT;
    objectTexture = textureManager.gameObjectsTexture; 
    renderRects.posOnTexture = {128,0,64,32};
    objectHealth = 1;
}

void CropMulcherObject::handleClick(Item* clickedBy){
    if(clickedBy->itemType == ItemCodes::CARROT || clickedBy->itemType == ItemCodes::YUCCAROOT){
        numItemsProcessing += clickedBy->numberOfItems;
        if(numItemsProcessing > maxProcessed){
            int leftoverItems = numItemsProcessing - maxProcessed; 
            numItemsProcessing = maxProcessed;
            clickedBy->numberOfItems = leftoverItems;
        }
        else{
            clickedBy->requestDeletion = true;
        }
        activate();
    }
}

bool CropMulcherObject::activate(){
    if(!processing){
        processing = true; 
        itemProcessingStart = std::chrono::steady_clock::now();
        renderRects.posOnTexture.y += 32;    
        return true;
    }
    return false;
}

bool CropMulcherObject::deactivate(){
    if(processing){
        processing = false;
        renderRects.posOnTexture.y -= 32;
        return true;
    }
    return false;
}

void CropMulcherObject::update(){
    GameObject::update();
    if(processing){
        auto curTime = std::chrono::steady_clock::now();
        auto secsElapsed = std::chrono::duration_cast<std::chrono::seconds>(curTime - itemProcessingStart).count();
        if(secsElapsed > 5){
            numItemsProcessing--;
            itemProcessingStart = curTime;
            GameObject::dropObject(ItemCodes::SOULSHARD,1,xTile + 6,yTile);
            if(numItemsProcessing == 0){
                deactivate();
            }
        }
    }
}