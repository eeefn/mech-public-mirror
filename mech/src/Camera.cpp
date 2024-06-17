#include "../headers/Camera.h"
#include "../headers/Map.h"
#include "../headers/constants.h"
#include "../headers/entities/Player.h"
#include "../headers/WindowManager.h"
#include "../headers/TextureManager.h"
#include <iostream>


Camera camera;
Camera::Camera(){
    xOffset = 0; yOffset = 0;
    renTile.x = 0; renTile.y = 0;
	renTile.w = TILE_DIM; renTile.h = TILE_DIM;
    objTex.x = 0; objTex.y = 0;
	objTex.w = TILE_DIM; objTex.h = TILE_DIM;
    initializeTileSelect();
}

void Camera::setCameraTarget(Entity *newCameraTarget){
	camera.cameraTarget = newCameraTarget;
}

void Camera::initializeCamera(int height,int width){
    this->tilesPerWindowHeight = (height + TILE_DIM - 1) / TILE_DIM;
    this->tilesPerWindowWidth = (width + TILE_DIM - 1) / TILE_DIM;
	this->cameraTarget = &player;
}

int Camera::getXPosWithinFrame(int xPos){	
	return xPos - xFrameOffset;
}

int Camera::getYPosWithinFrame(int yPos){
	int cameraOffset = this->cameraTarget->posY - (WINDOW_HEIGHT / 2 - 56);
	if (cameraOffset > 0){
		return yPos - cameraOffset;
	}
	else{
		return yPos;
	}
}

void Camera::initializeTileSelect(){
    for (unsigned int i = 0; i < TILE_WIDTH_IN_TILE_MAP; i++) {
		for (unsigned int j = 0; j < TILE_WIDTH_IN_TILE_MAP; j++) {
			tileSelect[i][j].x = TEX_DIM * j;
			tileSelect[i][j].y = TEX_DIM * i;
			tileSelect[i][j].w = TEX_DIM;
			tileSelect[i][j].h = TEX_DIM;
		}
	}
}

void Camera::renderMap(){
	int xOffsetCameraTarget = 0;
	if (xFrameOffset > 0) {
		xOffsetCameraTarget = (cameraTarget->posX % TILE_DIM);
	}
	int yOffsetCameraTarget = 0;
	if (cameraTarget->posY > (WINDOW_HEIGHT / 2 - cameraTarget->entityHeight / 2 - 8)) {
		yOffsetCameraTarget = (cameraTarget->posY % TILE_DIM);
	}
	//Iterate through every tile in the frame
    for (int y = yOffset; y <= tilesPerWindowHeight + yOffset; y++) {
		for (int x = xOffset; x <= tilesPerWindowWidth + xOffset; x++) {
			renTile.x = ((x - xOffset) * TILE_DIM) - xOffsetCameraTarget;
			renTile.y = ((y - yOffset) * TILE_DIM) - yOffsetCameraTarget;
			//grab the number representing the texture we should have for the given tile from the map
			short texSel = map.tileMap[y][x];
			if (texSel > 0) {
				SDL_RenderCopy(windowManager.renderer, textureManager.tileTexture, textureSelect(texSel), &renTile);
			}
			else {
				//find the object at the location
				for (auto &obj:map.gameObjList) {
					if ((obj->xTile == x) && (obj->yTile == y)) {
						//change the rendering tile size to render our object
						renTile.h = obj->height;
						renTile.w = obj->width;
						objTex.h = obj->height;
						objTex.w = obj->width;
						objTex.x = obj->spriteSheetXPos;
						objTex.y = obj->spriteSheetYPos;
						SDL_RenderCopy(windowManager.renderer, textureManager.gameObjectTexture,NULL,&renTile);
					}
				}
				renTile.w = TILE_DIM;
				renTile.h = TILE_DIM;
			}

		}
	}
    return;
}

/*Return a reference to a rect that has the location of the correct tile texture*/
SDL_Rect* Camera::textureSelect(short select) {
	int texSelX = select;
	int texSelY = 0;
	if (select > (TILE_WIDTH_IN_TILE_MAP - 1)) {
		texSelX = ((select + 1) % TILE_WIDTH_IN_TILE_MAP) - 1;
		texSelY = ((select + 1) / TILE_WIDTH_IN_TILE_MAP);
	}
	return &tileSelect[texSelY][texSelX];
}

void Camera::update(){	
	updateCameraOffsets();
	updateTargetDisplayPos();	
}

void Camera::updateCameraOffsets(){
	xFrameOffset = cameraTarget->posX - (WINDOW_WIDTH / 2 ) + (cameraTarget->entityWidth / 2);
	if(xFrameOffset < 0 ){
		xFrameOffset = 0;
	}
	camera.xOffset = (cameraTarget->posX) / TILE_DIM - (WINDOW_WIDTH / 2 - cameraTarget->entityWidth / 2) / TILE_DIM;
	camera.yOffset = (cameraTarget->posY) / TILE_DIM - (WINDOW_HEIGHT / 2 - cameraTarget->entityHeight / 2) / TILE_DIM;
}

void Camera::updateTargetDisplayPos(){
	if (camera.xOffset >= 0) {
		cameraTarget->displayRect.x = cameraTarget->posX - (camera.xOffset * TILE_DIM) - cameraTarget->posX % TILE_DIM;
	}
	else {
		camera.xOffset = 0;
		cameraTarget->displayRect.x = cameraTarget->posX - (camera.xOffset * TILE_DIM);
	}
	if (camera.yOffset >= 0) {
		cameraTarget->displayRect.y = cameraTarget->posY - (camera.yOffset * TILE_DIM) - cameraTarget->posY % TILE_DIM;
	}
	else {
		camera.yOffset = 0;
		cameraTarget->displayRect.y = cameraTarget->posY - (camera.yOffset * TILE_DIM);
	}
}