#include "../../headers/items/SoulFishingRodItem.h"
#include "../../headers/items/ItemCodes.h"

SDL_Rect* SoulFishingRodItem::spriteSheetPos = new SDL_Rect {0,64,16,16};

SoulFishingRodItem::SoulFishingRodItem() : ToolItem(ItemCodes::SOULFISHINGROD){
    return;
}

SDL_Rect* SoulFishingRodItem::getSpriteSheetPos(){
    spriteSheetPos->x = getSpShXOffset();
    return spriteSheetPos;
}