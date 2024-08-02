#pragma once
#include <SDL.h>

class GameObject
{
	public:
		GameObject(short scale, int width, int height);
		int xTile, yTile;
		short ID;
		short objectScale;
		SDL_Rect spriteSheetPos;
		SDL_Rect renObj;
		int width, height;
		virtual bool place();
		virtual bool destroy();
		virtual bool activate();
		virtual bool deactivate();
		virtual void highlight(bool highlight);
		bool highlighted = false;
};

