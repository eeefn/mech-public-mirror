#include "../headers/Hotbar.h"
#include "../headers/TextureManager.h"
#include "../headers/WindowManager.h"

int Hotbar::hotbarScale = 3;

Hotbar::Hotbar(vector<Item*> *bar) : buildShadow(){
    barRef = bar;    
    slots = bar->size();
    initializeHotbar();
    itemPos = {0,0,16*hotbarScale,16*hotbarScale};
    selectPos = {getItemXPos(0) - 1 * hotbarScale,hotbarPosTop.y + 4 * hotbarScale,18*hotbarScale,18*hotbarScale};
    return;
}

bool Hotbar::handleClick(){
    if(buildShadow.placeShadowObject()){
        return true;
    }
    return false; 
}

void Hotbar::initializeHotbar(){
    int hotbarWidth = 198 * hotbarScale;
    int hotbarHeightTB = 4 * hotbarScale;
    int hotbarHeightM = 19 * hotbarScale;
    int hotbarXPos = (windowSize.WINDOW_WIDTH - hotbarWidth) / 2;
    int hotbarYPos = windowSize.WINDOW_HEIGHT - hotbarHeightM - (2 * hotbarHeightTB); 
    hotbarPosTop = {hotbarXPos,hotbarYPos,hotbarWidth,hotbarHeightTB};
    hotbarPosMid = {hotbarXPos,hotbarYPos + hotbarHeightTB,hotbarWidth,hotbarHeightM};
    hotbarPosBottom = {hotbarXPos,hotbarYPos + hotbarHeightTB + hotbarHeightM,hotbarWidth,hotbarHeightTB};
}

void Hotbar::render(){
    SDL_RenderCopy(windowManager.renderer,textureManager.inventoryTexture,&hotbarTexSelTop,&hotbarPosTop);
    SDL_RenderCopy(windowManager.renderer,textureManager.inventoryTexture,&hotbarTexSelMid,&hotbarPosMid);
    SDL_RenderCopy(windowManager.renderer,textureManager.inventoryTexture,&hotbarTexSelBottom,&hotbarPosBottom);
    for(int i = 0; i < slots; i++){
        if(barRef->at(i) != nullptr){
            SDL_Rect* itemTexturePos = barRef->at(i)->getSpriteSheetPos();
            itemPos.x = getItemXPos(i);
            itemPos.y = hotbarPosTop.y + 5 * hotbarScale;
            SDL_RenderCopy(windowManager.renderer,textureManager.itemsTexture,itemTexturePos,&itemPos);
        }
    }
    SDL_RenderCopy(windowManager.renderer,textureManager.inventoryTexture, &selectRectTexSel,&selectPos);
    buildShadow.render();
    return;
}

void Hotbar::update(){
    buildShadow.update();    
}

int Hotbar::getItemXPos(int xInvenPos){
	int firstItemPos = hotbarPosTop.x + 10 * hotbarScale;
	int itemOffset = xInvenPos * ((2 + 16) * hotbarScale);
	return firstItemPos + itemOffset;	
}

void Hotbar::setSelectedSlot(int setTo){
    if(setTo < slots && setTo >= 0){
        selectedSlot = setTo;
        selectedItem = barRef->at(setTo);
        if(selectedItem != nullptr){
            selectPos.x = getItemXPos(setTo) - 1 * hotbarScale;
            if(selectedItem->objectPlaced > 0){
                buildShadow.setShadowObject(selectedItem->objectPlaced);
            }
            else{
                buildShadow.destroyShadowObject();
            }           
        }
        else{
            selectPos.x = getItemXPos(setTo) - 1 * hotbarScale;
            buildShadow.destroyShadowObject();
        }
        
    }
}

Item* Hotbar::getItemAtSelectedSlot(){
    selectedItem = barRef->at(selectedSlot);
    return selectedItem; 
}

void Hotbar::incrementSelectedSlot(){
    setSelectedSlot((selectedSlot + 1) % slots);
}
void Hotbar::decrementSelectedSlot(){
    int sSlot = (selectedSlot - 1) % slots;
    if(sSlot < 0){
        sSlot = slots - 1;
    }
    setSelectedSlot(sSlot);
}