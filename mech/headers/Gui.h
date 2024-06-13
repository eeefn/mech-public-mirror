#pragma once
#include <SDL.h>
#include "../headers/entities/Entity.h"

class Gui
{
	public:
		//array of rects for displaying the right tile from gui
		void render(int gameMode);
		void renderEditorSelection();
		void renderSoul();
		void setupSelector(Entity* playerEntity);
		void expandSelWindowLeft();
		void expandSelWindowRight();
		void expandSelWindowDown();
		void expandSelWindowUp();
		void moveSelWindowLeft();
		void moveSelWindowRight();
		void moveSelWindowDown();
		void moveSelWindowUp();
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