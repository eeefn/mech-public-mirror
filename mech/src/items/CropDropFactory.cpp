#include "../../headers/items/CropDropFactory.h"
#include <unordered_map>

CropDropFactory::CropDropFactory(){
    
}

std::vector<int> CropDropFactory::getCropsDroppedBySeed(int itemCodeOfSeed){
    std::unordered_map<int, std::vector<int>> seedToCropMap{
        {ItemCodes::YUCCASEED,{ItemCodes::YUCCALEAF,ItemCodes::YUCCAROOT}},
        {ItemCodes::CARROTSEED,{ItemCodes::CARROT}}
    };
    auto mapIt = seedToCropMap.find(itemCodeOfSeed);
    if(mapIt != seedToCropMap.end()){
        return mapIt->second;
    }
    else{
        return {};
    }
}