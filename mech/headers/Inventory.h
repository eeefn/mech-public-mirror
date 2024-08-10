#pragma once
#include "./items/Item.h"
#include <vector>
using std::vector;

struct InventoryPosition{
	int slotsX;
	int slotsY;
};

class Inventory{
    public:
        Inventory(int slotsX, int slotsY, int stackLimit);
		void initializeInventory();

        static int inventoryScale;
		SDL_Rect numArr[10];
        InventoryPosition inventorySize;
		InventoryPosition slotClicked;
		void handleInventoryClick(int xPos, int yPos,Uint32 clickType);
		void renderInventory();
        bool addToInventory(Item* itemToAdd);
    private:
        int stackLimit;
		SDL_Rect inventoryPos;
		SDL_Rect itemPos = {0,0,16*inventoryScale,16*inventoryScale};
        vector<vector<Item*>> inventory;
		Item* heldItem = nullptr;
		Item* itemAtClick = nullptr;
		bool setSlotClicked(int xPosClicked,int yPosClicked);
		void placeItem(int num);
		void placeItem();
		void pickItem();
		void placeOne();
		void pickHalf();
		void renderNumber(int num, int xPos, int yPos,SDL_Renderer* rend);
		int getItemXPos(int xInvenPos);
		int getItemYPos(int yInvenPos);
		int getInvPosFromXPos(int xPos);
		int getInvPosFromYPos(int yPos);
};