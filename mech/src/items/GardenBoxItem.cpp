#include "../../headers/items/GardenBoxItem.h"
#include "../../headers/items/ItemCodes.h"

SDL_Rect* GardenBoxItem::spriteSheetPos = new SDL_Rect {32,0,16,16};

SDL_Rect* GardenBoxItem::getSpriteSheetPos(){
    return spriteSheetPos;
}

GardenBoxItem::GardenBoxItem(int numItems) : Item(numItems,ItemCodes::GARDENBOX){
    return;
}