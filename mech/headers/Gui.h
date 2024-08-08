#pragma once
#include <SDL.h>

class Gui
{
	public:
		struct SoulColors{
			constexpr static int BLACK = 0;
			constexpr static int WHITE = 1;
			constexpr static int BROWN = 2;
			constexpr static int ORANGE = 3;
			constexpr static int RED = 4;
			constexpr static int GREEN = 5;
			constexpr static int BLUE = 6;
			constexpr static int PURPLE = 7;
		}soulColors;

		int pulseCount = 0;
		void setSoulColor(int color);
		void render(int gameMode);
		void toggleInventory();
		void initializeInventory();
        int inventoryScale = 3;
		Gui();
	private:
		bool inventoryOpen = false;
		void renderSoul();
		void renderInventory();
		int soulColor = 0;
		SDL_Rect guiArr[8][22];
		SDL_Rect guiComponent = {16, 16, 48, 48};
		SDL_Rect selWindowRen;
		SDL_Rect inventoryPos;

};

extern Gui gui;