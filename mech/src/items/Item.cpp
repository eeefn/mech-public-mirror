#include "../../headers/items/Item.h"
#include <cmath>

Item::Item(int numItems,int itType){
   if(numItems < 0){
      numItems = 0;
   }
   else if(numItems >= 128){
      numItems = 128;
   }
   numberOfItems = numItems;
   itemType = itType;
   yAcc = 250;
   return;
}

Item::~Item(){
    return;
}

SDL_Rect* Item::getSpriteSheetPos(){
   return NULL; 
}

void Item::update(float dt){
   if (yAcc > 250) {
      yAcc = 250;
   }
   yVel += yAcc * dt;
   if (yVel >= 200) {
      yVel = 200;
   }
   yPos += round(yVel * dt);
   return;
}