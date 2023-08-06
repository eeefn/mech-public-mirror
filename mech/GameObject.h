#pragma once

class GameObject
{
	public:
		int spriteSheetXPos, spriteSheetYPos;
		int xTile, yTile;
		short ID;
		int width, height;
		bool place();
		bool destroy();
		bool activate();
		bool deactivate();
};

