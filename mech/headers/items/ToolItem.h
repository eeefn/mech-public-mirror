#pragma once
#include "Item.h"

class ToolItem : public Item{
    public:
        ToolItem(int itemCode);
        int getSpShXOffset();
        int damagePerFrame = 0;
    private:
        bool checkBroken();
        int getSoulColor();
};