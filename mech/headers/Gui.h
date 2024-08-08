#pragma once
#include <SDL.h>

class Gui
{
	public:
		int pulseCount = 0;
		void render(int gameMode);
		void initializeInventory();
        int inventoryScale = 3;
		Gui();
	private:
		void renderSoul();
		void renderInventory();
		int getItemXPos(int xInvenPos);
		int getItemYPos(int yInvenPos);
		SDL_Rect guiArr[8][22];
		SDL_Rect guiComponent = {16, 16, 48, 48};
		SDL_Rect selWindowRen;
		SDL_Rect inventoryPos;
		SDL_Rect itemPos = {0,0,16*inventoryScale,16*inventoryScale};

};

extern Gui gui;