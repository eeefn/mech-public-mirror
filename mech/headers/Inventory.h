#pragma once
#include "items/Item.h"
#include "RenderRects.h"
#include "CraftingWindow.h"
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
		bool handleInventoryClick(int xPos, int yPos,Uint32 clickType);
		void renderInventory();
		void update();
        bool addToInventory(Item* itemToAdd);
        bool craftRecipe(Recipe* recipeToCraft);
		void deleteFromInventory(Item* itemToDelete);
		vector<Item*>* getInventoryRow(int rowToGet);
		RenderRect renderRect;
    private:
        int stackLimit;
		SDL_Rect itemPos = {0,0,16*inventoryScale,16*inventoryScale};
        vector<vector<Item*>> inventory;
		Item* heldItem = nullptr;
		Item* itemAtClick = nullptr;
		bool setSlotClicked(int xPosClicked,int yPosClicked);
		bool checkIfItemQuantityExists(Ingredient ingredient);
		bool removeFromInventory(Ingredient Ingredient);
		void placeItem();
		void pickItem();
		void placeOne();
		void pickHalf();
		void renderNumber(int num, int xPos, int yPos,SDL_Renderer* rend);
		int getItemXPos(int xInvenPos);
		int getItemYPos(int yInvenPos);
		int getInvPosFromXPos(int xPos);
		int getInvPosFromYPos(int yPos);
		void manageDeletedItems();
};