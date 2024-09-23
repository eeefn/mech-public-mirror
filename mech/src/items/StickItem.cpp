#include "../../headers/items/StickItem.h"
#include "../../headers/items/ItemCodes.h"

SDL_Rect* StickItem::spriteSheetPos = new SDL_Rect {16,0,16,16};

SDL_Rect* StickItem::getSpriteSheetPos(){
    return spriteSheetPos;
}

StickItem::StickItem(int numItems) : Item(numItems,ItemCodes::STICK){
    return;
}