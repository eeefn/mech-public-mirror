#include "../../headers/gameObjects/Mushroom.h"
#include "../../headers/TextureManager.h"

Mushroom::Mushroom(short mType, short id, int xT, int yT) : GameObject(2,16,16) {
	mushType = mType;
	objectTexture = textureManager.gameObjectTexture;
	xTile = xT;
	yTile = yT;
	renderRects.posOnTexture = {0,0,16,16};
	renderRects.posOnScreen = {0,0,scaledWidth,scaledHeight};
	ID = id;
}

void Mushroom::render(SDL_Renderer* rend){
	GameObject::render(rend);
	if(highlighted){
		renderRects.posOnTexture.x = 16;
		SDL_RenderCopy(rend,objectTexture,&renderRects.posOnTexture,&renderRects.posOnScreen);
		renderRects.posOnTexture.x = 0;
	}
}
bool Mushroom::highlight(const std::string& srcEntityId){
	if(srcEntityId == "SOUL_SPRITE"){
		highlighted = true;
	}
	else{
		highlighted = false;
	}
	return highlighted;
}