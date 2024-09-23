#include "../../headers/items/YuccaRootItem.h"
#include "../../headers/items/ItemCodes.h"

SDL_Rect* YuccaRootItem::spriteSheetPos = new SDL_Rect {96,0,16,16};

SDL_Rect* YuccaRootItem::getSpriteSheetPos(){
    return spriteSheetPos;
}

YuccaRootItem::YuccaRootItem(int numItems) : Item(numItems,ItemCodes::YUCCAROOT){
    renderRectRefs.posOnTexture = spriteSheetPos;
    return;
}
