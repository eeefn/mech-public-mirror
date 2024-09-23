#include "../../headers/items/CarrotSeedItem.h"
#include "../../headers/items/ItemCodes.h"

SDL_Rect* CarrotSeedItem::spriteSheetPos = new SDL_Rect {48,0,16,16};

SDL_Rect* CarrotSeedItem::getSpriteSheetPos(){
    return spriteSheetPos;
}

CarrotSeedItem::CarrotSeedItem(int numItems) : Item(numItems,ItemCodes::CARROTSEED){
    renderRectRefs.posOnTexture = spriteSheetPos;
    return;
}