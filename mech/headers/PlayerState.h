#include "../headers/Gui.h"
#include "../headers/items/Item.h"

class PlayerState {
    friend class Gui; 
    public:
        PlayerState();
		void toggleInventory();
        void setSoulColor(int color);
        bool addToInventory(Item* itemToAdd);
        bool inventoryOpen = false;
    private:
        int soul = 100;
        int soulColor = 0;
        Item* inventory[3][10] = {nullptr};
};

extern PlayerState playerState;