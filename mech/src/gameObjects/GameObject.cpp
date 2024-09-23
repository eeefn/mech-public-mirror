#include "../../headers/gameObjects/GameObject.h"
#include "../../headers/Camera.h"

GameObject::GameObject(short scale, int w, int h){
	objectScale = scale;
	scaledWidth = scale * w;
	scaledHeight = scale * h;
	renderRects.posOnScreen = {0,0,scaledWidth,scaledHeight};
}
GameObject::GameObject(){
	
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

bool GameObject::highlight(const std::string& srcEntityId){
	return false;
}

void GameObject::handleClick(Item *clickedBy){
	
}

void GameObject::render(SDL_Renderer* rend){
	SDL_RenderCopy(rend,objectTexture,&renderRects.posOnTexture,&renderRects.posOnScreen);
}

void GameObject::update(){
	renderRects.posOnScreen.x = camera.getXPosWithinFrame(xTile * mapInfo.TILE_DIM);
	renderRects.posOnScreen.y = camera.getYPosWithinFrame(yTile * mapInfo.TILE_DIM);
}

void GameObject::dropObject(int itemCode,int itemCount, int xTile, int yTile){
	int xPos = xTile * mapInfo.TILE_DIM;
	int yPos = yTile * mapInfo.TILE_DIM;
	itemManager.makeExternalItem(itemCode,itemCount,xPos,yPos);	
}