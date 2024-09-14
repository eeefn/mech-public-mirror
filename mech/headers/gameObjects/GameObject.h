#pragma once
#include <SDL.h>
#include <string>
#include "../RenderRects.h"
#include "../items/Item.h"
#include "../items/ItemManager.h"

class GameObject
{
	public:
		GameObject(short scale, int width, int height);
		virtual ~GameObject();
		int xTile, yTile;
		short ID;
		short objectScale;
		RenderRect renderRects;
		int scaledWidth, scaledHeight;
		bool highlighted = false;
		bool hasLeftNeighbor = false;
		bool hasRightNeighbor = false;
		bool markedForDeletion = false;
		virtual bool place();
		virtual bool destroy();
		virtual bool activate();
		virtual bool deactivate();
		virtual void render(SDL_Renderer* rend);
		virtual void update();
		virtual bool highlight(const std::string& srcEntityId);
		virtual void handleClick(Item *clickedBy);
	protected:
		SDL_Texture* objectTexture;
		int objectHealth;
		void dropObject(int itemCode,int itemCount, int xTile, int yTile);
};

