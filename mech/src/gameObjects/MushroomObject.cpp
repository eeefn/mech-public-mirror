#include "../../headers/gameObjects/MushroomObject.h"
#include "../../headers/TextureManager.h"

MushroomObject::MushroomObject(short mType, short id, int xT, int yT) : GameObject(2,16,16) {
	mushType = mType;
	objectTexture = textureManager.gameObjectsTexture;
	xTile = xT;
	yTile = yT;
	renderRects.posOnTexture = {96,0,16,16};
	renderRects.posOnScreen = {0,0,scaledWidth,scaledHeight};
	ID = id;
}

void MushroomObject::render(SDL_Renderer* rend){
	GameObject::render(rend);
	if(highlighted){
		renderRects.posOnTexture.x += 16;
		SDL_RenderCopy(rend,objectTexture,&renderRects.posOnTexture,&renderRects.posOnScreen);
		renderRects.posOnTexture.x -= 16;
	}
}

bool MushroomObject::highlight(const std::string& srcEntityId){
	if(srcEntityId == "SOUL_SPRITE"){
		highlighted = true;
	}
	else{
		highlighted = false;
	}
	return highlighted;
}