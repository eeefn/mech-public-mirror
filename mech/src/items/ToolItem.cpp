#include "../../headers/items/ToolItem.h"
#include "../../headers/PlayerState.h"

ToolItem::ToolItem(int itemCode) : Item(1,itemCode){
    return;
}

bool ToolItem::checkBroken(){
    if(playerState.getSoulVal() < 10){
        return true;
    }
    return false;
}

int ToolItem::getSoulColor(){
    return playerState.getSoulColor();
}

//get the spriteSheet xOffset for tools. Current Soul Color and whether or not the 
//tool is broken determines which tool texture is displayed. 
int ToolItem::getSpShXOffset(){
    int itemSheetXOffset = 16 * getSoulColor();
    if(!checkBroken()){
        itemSheetXOffset += 16*8;
    }
    return itemSheetXOffset;
}