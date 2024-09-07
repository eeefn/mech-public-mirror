#include "../../headers/items/ItemFactory.h"
#include "../../headers/items/RockItem.h"
#include "../../headers/items/StickItem.h"
#include "../../headers/items/SoulSwordItem.h"
#include "../../headers/items/SoulPickaxeItem.h"
#include "../../headers/items/SoulShovelItem.h"
#include "../../headers/items/SoulAxeItem.h"
#include "../../headers/items/SoulFishingRodItem.h"
#include "../../headers/items/ItemCodes.h"
#include "../../headers/items/GardenBoxItem.h"

using namespace ItemCodes;
ItemFactory itemFactory;

ItemFactory::ItemFactory(){
     gameItemFactory = {
        {ROCK, [](int itemCount) -> Item* {RockItem* rock = new RockItem(itemCount); return rock;}},
        {STICK,[](int itemCount) -> Item* {StickItem* stick = new StickItem(itemCount);return stick;}},
        {SOULSWORD,[](int itemCount) -> Item* {SoulSwordItem* sword = new SoulSwordItem();return sword;}},
        {SOULPICK,[](int itemCount) -> Item* {SoulPickaxeItem* pick = new SoulPickaxeItem();return pick;}},
        {SOULSHOVEL,[](int itemCount) -> Item* {SoulShovelItem* shovel = new SoulShovelItem();return shovel;}},
        {SOULAXE,[](int itemCount) -> Item* {SoulAxeItem* axe = new SoulAxeItem();return axe;}},
        {SOULFISHINGROD,[](int itemCount) -> Item* {SoulFishingRodItem* rod = new SoulFishingRodItem();return rod;}},
        {GARDENBOX,[](int itemCount) -> Item* {GardenBoxItem* box = new GardenBoxItem(itemCount);return box;}},
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