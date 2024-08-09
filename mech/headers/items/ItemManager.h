#pragma once
#include "Item.h"
#include "RockItem.h"
#include "ItemCodes.h"
#include <unordered_map>

using namespace ItemCodes;
class ItemManager{
    public:
        ItemManager();
        Item* makeItem(int itemCode, int itemCount);
        using ItemFactory = Item*(*)(int itemCount);
        std::unordered_map<int,ItemFactory> itemFactory = {
            {ROCK, [](int itemCount) -> Item* {RockItem* rock = new RockItem(itemCount); return rock;}} 
        };
};

extern ItemManager itemManager;