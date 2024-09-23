#include "../../headers/items/SoulShovelItem.h"
#include "../../headers/items/ItemCodes.h"

SDL_Rect* SoulShovelItem::spriteSheetPos = new SDL_Rect {0,48,16,16};

SoulShovelItem::SoulShovelItem() : ToolItem(ItemCodes::SOULSHOVEL){
    return;
}

SDL_Rect* SoulShovelItem::getSpriteSheetPos(){
    spriteSheetPos->x = getSpShXOffset();
    return spriteSheetPos;
}