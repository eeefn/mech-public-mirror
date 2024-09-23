#pragma once
#include <SDL.h>
#include "../headers/items/Item.h"

class Gui
{
	public:
		int pulseCount = 0;
		void render(int gameMode);
		Gui();
	private:
		void renderSoul();
		SDL_Rect guiArr[8][22];
		SDL_Rect guiComponent = {16, 16, 48, 48};
		SDL_Rect selWindowRen;

};

extern Gui gui;