#pragma once
#include "items/Item.h"
#include "RenderRects.h"
#include <vector>
#include <array>
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
		static constexpr std::array<SDL_Rect,10> numArr = []{
			std::array<SDL_Rect,10> ar{};
			for(int i = 0; i < 10;i++){
				ar[i] = {i * 3, 0, 3,6};
			}
			return ar;
		}();

        InventoryPosition inventorySize;
		InventoryPosition slotClicked;
		void handleInventoryClick(int xPos, int yPos,Uint32 clickType);
		void renderInventory();
        bool addToInventory(Item* itemToAdd);
		vector<Item*>* getInventoryRow(int rowToGet);
    private:
        int stackLimit;
		RenderRect renderRect;
//		SDL_Rect inventoryPos;
//		SDL_Rect invenTexSel = {0,0,198,75};
		SDL_Rect itemPos = {0,0,16*inventoryScale,16*inventoryScale};
        vector<vector<Item*>> inventory;
		Item* heldItem = nullptr;
		Item* itemAtClick = nullptr;
		bool setSlotClicked(int xPosClicked,int yPosClicked);
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