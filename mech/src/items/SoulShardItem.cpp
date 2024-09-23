#include "../../headers/items/SoulShardItem.h"
#include "../../headers/items/ItemCodes.h"

SDL_Rect* SoulShardItem::spriteSheetPos = new SDL_Rect {128,0,16,16};

SDL_Rect* SoulShardItem::getSpriteSheetPos(){
    return spriteSheetPos;
}

SoulShardItem::SoulShardItem(int numItems) : Item(numItems,ItemCodes::SOULSHARD){
    renderRectRefs.posOnTexture = spriteSheetPos;
}