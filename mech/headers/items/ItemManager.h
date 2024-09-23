#pragma once
#include "Item.h"
#include "ItemFactory.h"
#include <vector>

class ItemManager{
    public:
        ItemManager();
        void makeExternalItem(int itemCode, int itemCount, int xPos, int yPos);
        void updateItems(float dt);
        void renderItems();
    private:
        void handleItemCollisions();
        std::vector<Item*> itemList;
};

extern ItemManager itemManager;