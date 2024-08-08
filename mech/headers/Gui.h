#pragma once
#include <SDL.h>
#include "../headers/items/Item.h"
class Gui
{
	public:
		int pulseCount = 0;
		void render(int gameMode);
		void initializeInventory();
		void handleGuiClick(int xPos, int yPos);
        int inventoryScale = 3;
		Gui();
	private:
		void placeItem(Item* itemAtClick, int xSlot, int ySlot);
		void pickItem(Item* itemAtClick, int xSlot, int ySlot);
		void renderSoul();
		void renderInventory();
		void renderNumber(int num, int xPos, int yPos,SDL_Renderer* rend);
		int getItemXPos(int xInvenPos);
		int getItemYPos(int yInvenPos);
		int getInvPosFromXPos(int xPos);
		int getInvPosFromYPos(int yPos);
		SDL_Rect guiArr[8][22];
		SDL_Rect numArr[10];
		SDL_Rect guiComponent = {16, 16, 48, 48};
		SDL_Rect selWindowRen;
		SDL_Rect inventoryPos;
		SDL_Rect itemPos = {0,0,16*inventoryScale,16*inventoryScale};
		Item* heldItem = nullptr;	

};

extern Gui gui;