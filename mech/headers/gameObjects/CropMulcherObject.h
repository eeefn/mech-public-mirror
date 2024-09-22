#pragma once
#include "GameObject.h"
#include <chrono>

class CropMulcherObject : public GameObject{
    public:
        CropMulcherObject(short id, int xT, int yT);
        void handleClick(Item* clickedBy);
        bool activate();
        bool deactivate();
        void update();
    private:
        std::chrono::steady_clock::time_point itemProcessingStart;
        int processingTime;
        int numItemsProcessing = 0;
        bool processing = false;
        int maxProcessed = 128;
};