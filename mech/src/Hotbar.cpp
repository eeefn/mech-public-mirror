#include "../headers/Hotbar.h"
#include "../headers/TextureManager.h"
#include "../headers/WindowManager.h"

int Hotbar::hotbarScale = 3;

Hotbar::Hotbar(vector<Item*> *bar){
    barRef = bar;    
    slots = bar->size();
    initializeHotbar();
    itemPos = {0,0,16*hotbarScale,16*hotbarScale};
    selectPos = {getItemXPos(0) - 1 * hotbarScale,hotbarPosTop.y + 4 * hotbarScale,18*hotbarScale,18*hotbarScale};
    return;
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
    return;
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
       selectPos.x = getItemXPos(setTo) - 1 * hotbarScale;
    }
}

Item* Hotbar::getItemAtSelectedSlot(){
    selectedItem = barRef->at(selectedSlot);
    return selectedItem; 
}

void Hotbar::incrementSelectedSlot(){
    selectedSlot = (selectedSlot + 1) % slots;
    selectedItem = barRef->at(selectedSlot);
    selectPos.x = getItemXPos(selectedSlot) - 1 * hotbarScale;
}
void Hotbar::decrementSelectedSlot(){
    selectedSlot = (selectedSlot - 1) % slots;
    if(selectedSlot < 0){
        selectedSlot = slots - 1;
    }
    selectedItem = barRef->at(selectedSlot);
    selectPos.x = getItemXPos(selectedSlot) - 1 * hotbarScale;
}