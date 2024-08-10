#pragma once
#include "Item.h"
#include <unordered_map>
class ItemFactory{
    public:
        ItemFactory();
        Item* makeItem(int itemCode, int itemCount);
        using GameItemFactory = Item*(*)(int itemCount);
        std::unordered_map<int,GameItemFactory> gameItemFactory;
};

extern ItemFactory itemFactory;