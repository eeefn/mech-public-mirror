#include "../../headers/items/YuccaSeedItem.h"
#include "../../headers/items/ItemCodes.h"

SDL_Rect* YuccaSeedItem::spriteSheetPos = new SDL_Rect {64,0,16,16};

SDL_Rect* YuccaSeedItem::getSpriteSheetPos(){
    return spriteSheetPos;
}

YuccaSeedItem::YuccaSeedItem(int numItems) : Item(numItems,ItemCodes::YUCCASEED){
    renderRectRefs.posOnTexture = spriteSheetPos;
}