#pragma once
#include "ResourceObject.h"
#include <SDL.h>
class RockObject : public ResourceObject{
    public:
        RockObject(short id, int xT, int yT, short rockType);
};