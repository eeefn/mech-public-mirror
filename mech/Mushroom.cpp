#include "Mushroom.h"

Mushroom::Mushroom(short mType, short id, int xT, int yT) {
	this->mushType = mType;
	xTile = xT;
	yTile = yT;
	height = MUSH_HEIGHT;
	width = MUSH_WIDTH;
	ID = id;
	spriteSheetXPos = SPRITESHEET_X_POS;
	spriteSheetYPos = SPRITESHEET_Y_POS;
}