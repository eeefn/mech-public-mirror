#include "../../headers/gameObjects/GameObject.h"
#include "../../headers/Camera.h"

GameObject::GameObject(short scale, int w, int h){
	objectScale = scale;
	width = scale * w;
	height = scale * h;
	renObj = {0,0,width,height};
}
GameObject::~GameObject(){

}

bool GameObject::place() {
	return false;
}

bool GameObject::destroy() {
	return false;
}

bool GameObject::activate() {
	return false;
}

bool GameObject::deactivate(){
	return false;
}
void GameObject::render(SDL_Renderer* rend){
	SDL_RenderCopy(rend,objectTexture,&spriteSheetPos,&renObj);
}

bool GameObject::highlight(const std::string& srcEntityId){
	return false;
}


void GameObject::update(){
	renObj.x = camera.getXPosWithinFrame(xTile * mapInfo.TILE_DIM);
	renObj.y = camera.getYPosWithinFrame(yTile * mapInfo.TILE_DIM);
}