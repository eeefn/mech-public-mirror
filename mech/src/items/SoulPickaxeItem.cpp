#include "../../headers/items/SoulPickaxeItem.h"
#include "../../headers/items/ItemCodes.h"

SDL_Rect* SoulPickaxeItem::spriteSheetPos = new SDL_Rect {0,32,16,16};

SoulPickaxeItem::SoulPickaxeItem() : ToolItem(ItemCodes::SOULPICK){
    damagePerFrame = 1;
    return;
}

SDL_Rect* SoulPickaxeItem::getSpriteSheetPos(){
    spriteSheetPos->x = getSpShXOffset();
    return spriteSheetPos;
}