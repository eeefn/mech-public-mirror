#include "../../headers/items/SoulSwordItem.h"
#include "../../headers/items/ItemCodes.h"

SDL_Rect* SoulSwordItem::spriteSheetPos = new SDL_Rect {16,16,16,16};

SoulSwordItem::SoulSwordItem(int numItems) : Item(numItems,ItemCodes::SOULSWORD){
    return;
}

SDL_Rect* SoulSwordItem::getSpriteSheetPos(){
    return spriteSheetPos;
}