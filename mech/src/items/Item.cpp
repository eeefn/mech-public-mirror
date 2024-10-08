#include "../../headers/items/Item.h"
#include <cmath>

Item::Item(int numItems,int itType){
   xPos = 0;
   yPos = 0;
   if(numItems < 0){
      numItems = 0;
   }
   else if(numItems >= 128){
      numItems = 128;
   }
   numberOfItems = numItems;
   itemType = itType;
   yAcc = 250;
   yVel = 0;
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

bool Item::operator<(const Item& other) const{
   return numberOfItems < other.numberOfItems;   
}
Item Item::operator++(){
   if(numberOfItems + 1 <= stackLimit){
      numberOfItems++;
   }
   return *this;
}

Item Item::operator--(){
   numberOfItems--;
   if(numberOfItems <= 0){
      requestDeletion = true;
   }
   return *this;
}