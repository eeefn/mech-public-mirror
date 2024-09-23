#pragma once
#include "GameObject.h"

class ResourceObject : public virtual GameObject{
    public: 
        ResourceObject(int itemCode, int numDropped, int brokenBy);
        void handleClick(Item* clickedBy);
    protected:
        int droppedResourceItemCode;
        int numResourceDropped;
        int toolBrokenBy;
};