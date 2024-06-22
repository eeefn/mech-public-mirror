#pragma once
#include <SDL.h>

class Gui
{
	public:
		void render(int gameMode);
		void renderSoul();
		int soulColor = 0;
		int pulseCount = 0;
		short selectColor = 0;
		Gui();
	private:
		SDL_Rect guiArr[8][22];
		SDL_Rect guiComponent = {16, 16, 48, 48};
		SDL_Rect selWindowRen;

};

extern Gui gui;