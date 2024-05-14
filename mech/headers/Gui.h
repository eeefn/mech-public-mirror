#pragma once
#include <SDL.h>

class Gui
{
public:
	//array of rects for displaying the right tile from gui
	int soulColor;
	int pulseCount;
	short selectColor;
	SDL_Rect guiArr[8][22];
	SDL_Rect guiComponent;
	SDL_Rect selWindowRen;
	SDL_Texture* guiTex;
	void renderSoul(SDL_Renderer* rend);
	Gui();
};

extern Gui gui;

