#include "../../headers/items/Item.h"

Item::Item(int numItems){
   if(numItems < 0){
      numItems = 0;
   }
   else if(numItems >= 128){
      numItems = 128;
   }
   numberOfItems = numItems;
   return;
}

Item::~Item(){
    return;
}

SDL_Rect* Item::getSpriteSheetPos(){
   return NULL; 
}