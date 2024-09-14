#include "../../headers/items/CarrotItem.h"
#include "../../headers/items/ItemCodes.h"

SDL_Rect* CarrotItem::spriteSheetPos = new SDL_Rect {80,0,16,16};

SDL_Rect* CarrotItem::getSpriteSheetPos(){
    return spriteSheetPos;
}

CarrotItem::CarrotItem(int numItems) : Item(numItems,ItemCodes::CARROT){
    renderRectRefs.posOnTexture = spriteSheetPos;
    return;
}