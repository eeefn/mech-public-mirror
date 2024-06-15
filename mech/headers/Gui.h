#pragma once
#include <SDL.h>

class Gui
{
	public:
		//array of rects for displaying the right tile from gui
		void render(int gameMode);
		void renderSoul();
		int soulColor;
		int pulseCount;
		short selectColor;
		Gui();
	private:
		SDL_Rect guiArr[8][22];
		SDL_Rect guiComponent;
		SDL_Rect selWindowRen;

};

extern Gui gui;