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
    texSelX = 0; texSelY = 0;
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
	int cameraOffset = this->cameraTarget->posX - (WINDOW_WIDTH /2) + (cameraTarget->entityWidth /2);

	if (cameraOffset > 0){
		return xPos - cameraOffset;
	}
	else{
		return xPos;
	}
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
	this->cameraTarget = cameraTarget;
    for (int y = yOffset; y <= tilesPerWindowHeight + yOffset; y++) {
		for (int x = xOffset; x <= tilesPerWindowWidth + xOffset; x++) {
			//grab the texture we should have for the given tile from the map
			short texSel = map.tileMap[y][x];
			renTile.x = ((x - xOffset) * TILE_DIM);
			if (cameraTarget->posX > (WINDOW_WIDTH / 2 - cameraTarget->entityWidth / 2)) {
				renTile.x -= (cameraTarget->posX % TILE_DIM);
			}
			renTile.y = ((y - yOffset) * TILE_DIM);
			if (cameraTarget->posY > (WINDOW_HEIGHT / 2 - cameraTarget->entityHeight / 2 - 8)) {
				renTile.y -= (cameraTarget->posY % TILE_DIM);
			}
			if (texSel > 0) {
				textureSelect(texSel);
				//handle offsets in the left corner. I havent handled the right corner 0.0
				SDL_RenderCopy(windowManager.renderer, textureManager.tileTexture, &tileSelect[texSelY][texSelX], &renTile);
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

void Camera::textureSelect(short select) {
	if (select > (TILE_WIDTH_IN_TILE_MAP - 1)) {
		texSelX = ((select + 1) % TILE_WIDTH_IN_TILE_MAP) - 1;
		texSelY = ((select + 1) / TILE_WIDTH_IN_TILE_MAP);
	}
	else {
		texSelX = select;
		texSelY = 0;
	}
}

void Camera::update(){	
	updateCameraOffsets();
	updateTargetDisplayPos();	
}

void Camera::updateCameraOffsets(){
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