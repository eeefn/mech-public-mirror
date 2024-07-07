#pragma once
#include "GameObject.h"
//create an all new object
//place an existing object from tilemap
class Mushroom : public GameObject
{
    public:
        short mushType;
        Mushroom(short mType, short id, int xT, int yT);

};

