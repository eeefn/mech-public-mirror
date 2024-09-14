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
#include "../../headers/items/YuccaSeedItem.h"
#include "../../headers/items/CarrotSeedItem.h"
#include "../../headers/items/CarrotItem.h"
#include "../../headers/items/YuccaLeafItem.h"
#include "../../headers/items/YuccaRootItem.h"

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
        {YUCCASEED,[](int itemCount) -> Item* {YuccaSeedItem* yucca = new YuccaSeedItem(itemCount);return yucca;}},
        {CARROTSEED,[](int itemCount) -> Item* {CarrotSeedItem* carrot = new CarrotSeedItem(itemCount);return carrot;}},
        {CARROT,[](int itemCount) -> Item* {CarrotItem* carrot = new CarrotItem(itemCount);return carrot;}},
        {YUCCALEAF,[](int itemCount) -> Item* {YuccaLeafItem* leaf = new YuccaLeafItem(itemCount);return leaf;}},
        {YUCCAROOT,[](int itemCount) -> Item* {YuccaRootItem* root = new YuccaRootItem(itemCount);return root;}}
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