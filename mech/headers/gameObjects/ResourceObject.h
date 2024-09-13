
#pragma once
#include "GameObject.h"

class ResourceObject : public GameObject{
    public: 
        ResourceObject(short scale, int w, int h, int itemCode, int numDropped, int brokenBy);
        void handleClick(Item* clickedBy);
    protected:
        int droppedResourceItemCode;
        int numResourceDropped;
        int toolBrokenBy;
};