#include "../headers/Camera.h"
#include "../headers/Map.h"
#include "../headers/constants.h"
#include "../headers/WindowManager.h"
#include "../headers/TextureManager.h"

Camera camera;
Camera::Camera(){
    xOffset = 0; yOffset = 0;
    initializeTileSelect();
}

void Camera::setCameraTarget(Entity *newCameraTarget){
	camera.cameraTarget = newCameraTarget;
}

void Camera::initializeCamera(int height,int width, Entity* initialCameraTarget,SDL_DisplayMode dm){
	setCameraTarget(initialCameraTarget);
	frame = {0,0,dm.w,dm.h};
}

int Camera::getXPosWithinFrame(int xPos){
	return xPos - frame.x;
}

int Camera::getYPosWithinFrame(int yPos){
	return yPos - frame.y;
}
int Camera::getGlobalXPosFromFrame(int xPos){
	return xPos + frame.x;	
}

int Camera::getGlobalYPosFromFrame(int yPos){
	return yPos + frame.y;
}

void Camera::initializeTileSelect(){
    for (unsigned int i = 0; i < mapInfo.TILE_WIDTH_IN_TILE_MAP; i++) {
		for (unsigned int j = 0; j < mapInfo.TILE_WIDTH_IN_TILE_MAP; j++) {
			tileSelect[i][j].x = mapInfo.TEX_DIM * j;
			tileSelect[i][j].y = mapInfo.TEX_DIM * i;
			tileSelect[i][j].w = mapInfo.TEX_DIM;
			tileSelect[i][j].h = mapInfo.TEX_DIM;
		}
	}
}

void Camera::renderMap(){
	int xTileOffset = frame.x / mapInfo.TILE_DIM;
	int yTileOffset = frame.y / mapInfo.TILE_DIM;
	int pixelOffsetX = frame.x % mapInfo.TILE_DIM;
	int pixelOffsetY = frame.y % mapInfo.TILE_DIM;
	for(int xTile = 0; xTile <= frame.w/mapInfo.TILE_DIM; xTile++){
		for(int yTile = 0; yTile <= frame.h/mapInfo.TILE_DIM; yTile++){
			short textureType = map.tileMap[yTile + yTileOffset][xTile + xTileOffset];
			if(textureType > 0){
				renderTile = {xTile * mapInfo.TILE_DIM - pixelOffsetX,yTile * mapInfo.TILE_DIM - pixelOffsetY,mapInfo.TILE_DIM,mapInfo.TILE_DIM};
				SDL_RenderCopy(windowManager.renderer,textureManager.tileTexture,getTextureOfTile(textureType),&renderTile);
			}
		}
	}
}

/*Return a reference to a rect on the sprite sheet that covers the desired texture*/
SDL_Rect* Camera::getTextureOfTile(short texType){
	int texSelX = texType;
	int texSelY = 0;
	if (texType > (mapInfo.TILE_WIDTH_IN_TILE_MAP - 1)) {
		texSelX = ((texType + 1) % mapInfo.TILE_WIDTH_IN_TILE_MAP) - 1;
		texSelY = ((texType + 1) / mapInfo.TILE_WIDTH_IN_TILE_MAP);
	}
	return &tileSelect[texSelY][texSelX];
}

void Camera::update(){	
	updateCameraOffsets();
	updateFrame();
}

void Camera::updateFrame(){
	int frameEdgeX = cameraTarget->posX + ((cameraTarget->entityWidth + frame.w)/2); 
	int frameEdgeY = cameraTarget->posY + ((cameraTarget->entityHeight + frame.h)/2);
	if(frameEdgeX < frame.w){
		frameEdgeX = frame.w;
	}
	else if(frameEdgeX > mapInfo.MAX_LVL_WIDTH * mapInfo.TILE_DIM){
		frameEdgeX = mapInfo.MAX_LVL_WIDTH * mapInfo.TILE_DIM;
	}
	if(frameEdgeY < frame.h){
		frameEdgeY = frame.h;
	}
	else if(frameEdgeY > mapInfo.MAX_LVL_WIDTH * mapInfo.TILE_DIM){
		frameEdgeY = mapInfo.MAX_LVL_WIDTH * mapInfo.TILE_DIM;
	}
	frame = {frameEdgeX - frame.w,frameEdgeY - frame.h, frame.w, frame.h};
	return;	
}

void Camera::updateCameraOffsets(){
	camera.xOffset = (cameraTarget->posX) / mapInfo.TILE_DIM - (windowSize.WINDOW_WIDTH / 2 - cameraTarget->entityWidth / 2) / mapInfo.TILE_DIM;
	camera.yOffset = (cameraTarget->posY) / mapInfo.TILE_DIM - (windowSize.WINDOW_HEIGHT / 2 - cameraTarget->entityHeight / 2) / mapInfo.TILE_DIM;
}

void Camera::renderBackround(){
	SDL_RenderCopy(windowManager.renderer,textureManager.caveBackroundTexture,NULL,NULL);
}
void Camera::snapPointToTileMap(SDL_Point* pointToSnap){
	int globalX = getGlobalXPosFromFrame(pointToSnap->x);	
	pointToSnap->x = getXPosWithinFrame((globalX / mapInfo.TILE_DIM) * mapInfo.TILE_DIM);
	int globalY = getGlobalYPosFromFrame(pointToSnap->y);
	pointToSnap->y = getYPosWithinFrame((globalY / mapInfo.TILE_DIM) * mapInfo.TILE_DIM);
}
