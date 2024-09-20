#include "../headers/Gui.h"
#include "../headers/items/Item.h"
#include "../headers/Inventory.h"
#include "../headers/Hotbar.h"
#include "../headers/CraftingWindow.h"
class PlayerState {
    friend class Gui; 
    public:
        PlayerState();
        void handleInventoryClick(int xPos, int yPos,Uint32 clickType);
        bool addToInventory(Item* itemToAdd);
        bool requestCraft(Recipe* recipeToCraft);
		void toggleInventory();
        void setSoulColor(int color);
        int getSoulColor();
        int getSoulVal();
        void placeItemFromHotbar();
        void update();
        bool inventoryOpen = false;
    private:
		Inventory playerInventory = Inventory(10,3,128);
    public: 
        Hotbar hotbar = Hotbar(playerInventory.getInventoryRow(0));
        CraftingWindow craftingWindow = CraftingWindow(playerInventory.renderRect.posOnScreen.x,playerInventory.renderRect.posOnScreen.y);
    private:
        int soul = 100;
        int soulColor = 0;
};

extern PlayerState playerState;