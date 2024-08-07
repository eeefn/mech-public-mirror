
#pragma once
#include "GameObject.h"
#include <SDL.h>

class Rock : public GameObject{
    public:
        Rock(short id, int xT, int yT, short rockType);

};