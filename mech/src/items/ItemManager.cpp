#include "../../headers/items/ItemManager.h"

ItemManager itemManager;

ItemManager::ItemManager(){
   return; 
}

Item* ItemManager::makeItem(int itemCode, int itemCount){
    auto itemIterator = itemFactory.find(itemCode);
    if(itemIterator != itemFactory.end()){
        return itemIterator->second(itemCount);
    }
    return nullptr;
}