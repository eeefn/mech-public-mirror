#pragma once
#include "ItemCodes.h"
#include <vector>

class CropDropFactory{
    public:
        CropDropFactory();
        static std::vector<int> getCropsDroppedBySeed(int itemCodeOfSeed);
};