#pragma once
#include <SDL.h>
#include <string>

class GameObject
{
	public:
		GameObject(short scale, int width, int height);
		virtual ~GameObject();
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
		virtual void render(SDL_Renderer* rend);
		virtual void update();
		virtual bool highlight(const std::string& srcEntityId);
		bool highlighted = false;
	protected:
		SDL_Texture* objectTexture;
};

