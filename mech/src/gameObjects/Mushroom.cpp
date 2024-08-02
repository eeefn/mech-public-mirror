#include "../../headers/gameObjects/Mushroom.h"

Mushroom::Mushroom(short mType, short id, int xT, int yT) : GameObject(2,16,16) {
	mushType = mType;
	//objectScale = 2;
	xTile = xT;
	yTile = yT;
	spriteSheetPos = {0,0,16,16};
	ID = id;
	//width = objectScale * spriteSheetPos.w;
	//height = objectScale * spriteSheetPos.h;
}