#pragma once
#include "Item.h"

class ToolItem : public Item{
    public:
        ToolItem(int itemCode);
        int getSpShXOffset();
    private:
        bool checkBroken();
        int getSoulColor();
};