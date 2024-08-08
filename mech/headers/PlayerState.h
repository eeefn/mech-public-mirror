#include "../headers/Gui.h"

class PlayerState {
    friend class Gui; 
    public:
        PlayerState();
		void toggleInventory();
    private:
		int soulColor = 0;
		bool inventoryOpen = false;
};

extern PlayerState playerState;