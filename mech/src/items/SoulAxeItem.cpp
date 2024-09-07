#include "../../headers/items/SoulAxeItem.h"
#include "../../headers/items/ItemCodes.h"

SDL_Rect* SoulAxeItem::spriteSheetPos = new SDL_Rect {0,80,16,16};

SoulAxeItem::SoulAxeItem() : ToolItem(ItemCodes::SOULAXE){
    return;
}


SDL_Rect* SoulAxeItem::getSpriteSheetPos(){
    spriteSheetPos->x = getSpShXOffset();
    return spriteSheetPos;
}