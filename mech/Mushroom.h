#pragma once
#include "GameObject.h"
#include "./constants.h"
#define MUSH_WIDTH 32
#define MUSH_HEIGHT 32
#define SPRITESHEET_X_POS 0
#define SPRITESHEET_Y_POS 0
//two types of object creation- 
//create an all new object
//place an existing object from tilemap
class Mushroom :
    public GameObject
{
    public:
    short mushType;
    Mushroom(short mType, short id, int xT, int yT);

};

