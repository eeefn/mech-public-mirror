#include "../../headers/items/YuccaLeafItem.h"
#include "../../headers/items/ItemCodes.h"

SDL_Rect* YuccaLeafItem::spriteSheetPos = new SDL_Rect {112,0,16,16};

SDL_Rect* YuccaLeafItem::getSpriteSheetPos(){
    return spriteSheetPos;
}

YuccaLeafItem::YuccaLeafItem(int numItems) : Item(numItems,ItemCodes::YUCCALEAF){
    renderRectRefs.posOnTexture = spriteSheetPos;
    return;
}
