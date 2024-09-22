#include "../../headers/items/SoulSwordItem.h"
#include "../../headers/items/ItemCodes.h"

SDL_Rect* SoulSwordItem::spriteSheetPos = new SDL_Rect {0,16,16,16};

SoulSwordItem::SoulSwordItem() : ToolItem(ItemCodes::SOULSWORD){
    damagePerFrame = 1;
    return;
}

SDL_Rect* SoulSwordItem::getSpriteSheetPos(){
    spriteSheetPos->x = getSpShXOffset();
    return spriteSheetPos;
}