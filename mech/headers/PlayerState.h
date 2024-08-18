#include "../headers/Gui.h"
#include "../headers/items/Item.h"
#include "../headers/Inventory.h"

class PlayerState {
    friend class Gui; 
    public:
        PlayerState();
        void handleInventoryClick(int xPos, int yPos,Uint32 clickType);
        bool addToInventory(Item* itemToAdd);
		void toggleInventory();
        void setSoulColor(int color);
        bool inventoryOpen = false;
    private:
		Inventory playerInventory = Inventory(10,3,128);
        int soul = 100;
        int soulColor = 0;
};

extern PlayerState playerState;