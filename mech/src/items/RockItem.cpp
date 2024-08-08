#include "../../headers/items/RockItem.h"

SDL_Rect* RockItem::spriteSheetPos = new SDL_Rect {0,0,16,16};

SDL_Rect* RockItem::getSpriteSheetPos(){
    return spriteSheetPos;
}

RockItem::RockItem(int numItems) : Item(numItems){
    return;
}