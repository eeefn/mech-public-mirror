#include "../../headers/TextureManager.h"
#include "../../headers/items/ItemCodes.h"
#include "../../headers/gameObjects/ResourceObject.h"
#include "../../headers/gameObjects/GardenBoxObject.h"
#include "../../headers/gameObjects/GameObjectManager.h"

GardenBoxObject::GardenBoxObject(short id, int xT, int yT) : ResourceObject(2,32,32,ItemCodes::GARDENBOX,1,ItemCodes::SOULAXE) {
    ID = id;
    xTile = xT;
    yTile = yT;
    objectTexture = textureManager.gameObjectsTexture; 
    renderRects.posOnTexture = {0,64,32,32};
    objectHealth = 50;
}

void GardenBoxObject::update(){
    GameObject::update();
    updateSeedSlot(slotOne);
    if(!allSlotsOccupiedBySingleSeed){
        updateSeedSlot(slotTwo);
    }
}

void GardenBoxObject::updateSeedSlot(SeedSlot& slot){
    if(slot.occupied){
        if(slot.phase != 3){
            auto curTime = std::chrono::steady_clock::now();
            auto secsElapsed = std::chrono::duration_cast<std::chrono::seconds>(curTime - slot.phaseGrowthStart).count();
            if(secsElapsed > 2){
                slot.phase++;
                slot.phaseGrowthStart = curTime;
            }
        }
    }
}

void GardenBoxObject::handleClick(Item* clickedBy){
    ResourceObject::handleClick(clickedBy);
    if(clickedBy->itemType == ItemCodes::CARROTSEED || clickedBy->itemType == ItemCodes::YUCCASEED){
        if(!plantSeedInSlot(slotOne, clickedBy)){
            plantSeedInSlot(slotTwo,clickedBy);
        }
    }
    if(markedForDeletion){
        dropSlotsHeldItem(slotOne);
        if(slotTwo.occupied && slotTwo.seedType != ItemCodes::YUCCASEED){
            dropSlotsHeldItem(slotTwo);
        }
    }
}

bool GardenBoxObject::plantSeedInSlot(SeedSlot& slot,Item* seedClickedBy){
    if(!slot.occupied && !allSlotsOccupiedBySingleSeed){
        slot = {true, 0, seedClickedBy->itemType};
        --(*seedClickedBy);
        slotOne.phaseGrowthStart = std::chrono::steady_clock::now();
        if(seedClickedBy->itemType == ItemCodes::YUCCASEED){
            allSlotsOccupiedBySingleSeed = true;
            //GardenBoxFull
        }
        return true;
    }
    return false;
}
void GardenBoxObject::dropSlotsHeldItem(SeedSlot& cropSlot){
    if(cropSlot.occupied){
        if(cropSlot.phase == 3){
            //drop crop 
        }
        else{
            GameObject::dropObject(cropSlot.seedType,1,xTile,yTile);
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