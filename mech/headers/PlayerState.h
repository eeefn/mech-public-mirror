#include "../headers/Gui.h"
#include "../headers/items/Item.h"

class PlayerState {
    friend class Gui; 
    public:
        PlayerState();
		    void toggleInventory();
        void setSoulColor(int color);
    private:
      int soul = 100;
      int soulColor = 0;
      bool inventoryOpen = false;
      Item* inventory[3][10];
};

extern PlayerState playerState;