#include "../../headers/gameObjects/Mushroom.h"
#include "../../headers/TextureManager.h"

Mushroom::Mushroom(short mType, short id, int xT, int yT) : GameObject(2,16,16) {
	mushType = mType;
	objectTexture = textureManager.gameObjectTexture;
	xTile = xT;
	yTile = yT;
	spriteSheetPos = {0,0,16,16};
	renObj = {0,0,width,height};
	ID = id;
}

void Mushroom::render(SDL_Renderer* rend){
	GameObject::render(rend);
	if(highlighted){
		spriteSheetPos.x = 16;
		SDL_RenderCopy(rend,objectTexture,&spriteSheetPos,&renObj);
		spriteSheetPos.x = 0;
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