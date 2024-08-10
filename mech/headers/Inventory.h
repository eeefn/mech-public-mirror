#pragma once
#include "./items/Item.h"
#include <vector>
using std::vector;
class Inventory{
    public:
		void initializeInventory();
		SDL_Rect inventoryPos;
        static int inventoryScale;
        Inventory(int slotsX, int slotsY, int stackLimit);
		SDL_Rect numArr[10];
        struct InventorySize{
            int slotsX;
            int slotsY;
        };
        InventorySize inventorySize;
		void handleInventoryClick(int xPos, int yPos,Uint32 clickType);
		void renderInventory();
        bool addToInventory(Item* itemToAdd);
    private:
        int stackLimit;
        vector<vector<Item*>> inventory;
		Item* heldItem = nullptr;	
		SDL_Rect itemPos = {0,0,16*inventoryScale,16*inventoryScale};
		void placeItem(Item* itemAtClick, int xSlot, int ySlot);
		void pickItem(Item* itemAtClick, int xSlot, int ySlot);
		void placeOne(Item* itemAtClick, int xSlot, int ySlot);
		void pickHalf(Item* itemAtClick, int xSlot, int ySlot);
		void renderNumber(int num, int xPos, int yPos,SDL_Renderer* rend);
		int getItemXPos(int xInvenPos);
		int getItemYPos(int yInvenPos);
		int getInvPosFromXPos(int xPos);
		int getInvPosFromYPos(int yPos);
};