#include "../../headers/gameObjects/GameObjectFactory.h"
#include "../../headers/gameObjects/Portal.h"
#include "../../headers/gameObjects/RockObject.h"
#include "../../headers/gameObjects/MushroomObject.h" 
#include "../../headers/gameObjects/ShrubObject.h"
#include "../../headers/gameObjects/GardenBoxObject.h"
#include "../../headers/gameObjects/ShortGrassObject.h"
#include "../../headers/gameObjects/GameObjectCodes.h"

using namespace gameObjectCodes;

GameObjectFactory gameObjectFactory;

GameObjectFactory::GameObjectFactory(){
    objectFactory = {
        {MUSHROOM, [](int id, short xT, short yT) -> GameObject* {MushroomObject* mush = new MushroomObject(0,id,xT,yT); return mush;}}, 
        {PORTAL, [](int id, short xT, short yT) -> GameObject* {Portal* port = new Portal(id,xT,yT);return port;}},
        {ROCK_0, [](int id, short xT, short yT) -> GameObject* {RockObject* rock0 = new RockObject(id,xT,yT,0);return rock0;}},
        {ROCK_1, [](int id, short xT, short yT) -> GameObject* {RockObject* rock1 = new RockObject(id,xT,yT,1);return rock1;}},
        {ROCK_2, [](int id, short xT, short yT) -> GameObject* {RockObject* rock2 = new RockObject(id,xT,yT,2);return rock2;}},
        {SHRUB_0, [](int id, short xT, short yT) -> GameObject* {GameObject* shrub0 = new ShrubObject(id,xT,yT,0);return shrub0;}},
        {SHRUB_1, [](int id, short xT, short yT) -> GameObject* {GameObject* shrub1 = new ShrubObject(id,xT,yT,1);return shrub1;}},
        {SHRUB_2, [](int id, short xT, short yT) -> GameObject* {ShrubObject* shrub2 = new ShrubObject(id,xT,yT,2);return shrub2;}},
        {GARDENBOX_0, [](int id, short xT, short yT) -> GameObject* {GardenBoxObject* gardenBox0 = new GardenBoxObject(id,xT,yT,2,32,32);return gardenBox0;}},
        {SHORTGRASS_0, [](int id, short xT, short yT) -> GameObject* {ShortGrassObject* grass0 = new ShortGrassObject(id,xT,yT,0);return grass0;}},
        {SHORTGRASS_1, [](int id, short xT, short yT) -> GameObject* {ShortGrassObject* grass1 = new ShortGrassObject(id,xT,yT,1);return grass1;}},
    };
}

GameObject* GameObjectFactory::makeObject(short objectType, short xT, short yT){
    auto objIt = objectFactory.find(objectType);
    if(objIt != objectFactory.end()){
        return objIt->second(objectType,xT,yT);
    }
    else{
        return nullptr;
    }
}