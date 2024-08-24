#include "../../headers/items/ItemFactory.h"
#include "../../headers/items/RockItem.h"
#include "../../headers/items/StickItem.h"
#include "../../headers/items/SoulSwordItem.h"
#include "../../headers/items/ItemCodes.h"

using namespace ItemCodes;
ItemFactory itemFactory;

ItemFactory::ItemFactory(){
     gameItemFactory = {
        {ROCK, [](int itemCount) -> Item* {RockItem* rock = new RockItem(itemCount); return rock;}},
        {STICK,[](int itemCount) -> Item* {StickItem* stick = new StickItem(itemCount);return stick;}},
        {SOULSWORD,[](int itemCount) -> Item* {SoulSwordItem* sword = new SoulSwordItem(itemCount);return sword;}}
    };
   return; 
}

Item* ItemFactory::makeItem(int itemCode, int itemCount){
    auto itemIterator = gameItemFactory.find(itemCode);
    if(itemIterator != gameItemFactory.end()){
        return itemIterator->second(itemCount);
    }
    return nullptr;
}