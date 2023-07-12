#pragma once

class GameObject
{
	int xPos, yPos;

	public:
		bool place();
		bool destroy();
		bool activate();
		bool deactivate();
};

