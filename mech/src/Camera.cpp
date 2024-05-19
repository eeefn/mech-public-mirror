#include "../headers/Camera.h"
#include "../headers/Map.h"
#include "../headers/constants.h"
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

void Camera::initializeCamera(int height,int width, SDL_Renderer *renderer,SDL_Texture *tileTexture,SDL_Texture *objectTexture){
    this->tilesPerWindowHeight = (height + TILE_DIM - 1) / TILE_DIM;
    this->tilesPerWindowWidth = (width + TILE_DIM - 1) / TILE_DIM;
    this->tileTexture = tileTexture;
    this->objectTexture = objectTexture;
    this->renderer = renderer;
}
int Camera::getXPosWithinFrame(int xPos){
	if (cameraTarget->posX <= (WINDOW_WIDTH / 2 - cameraTarget->entityWidth / 2)){
		return xPos;
	}
	else{
		return xPos;//(xPos - (WINDOW_WIDTH / 2) - (cameraTarget->entityWidth / 2));
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

void Camera::renderMap(Entity *cameraTarget){
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
				SDL_RenderCopy(renderer, tileTexture, &tileSelect[texSelY][texSelX], &renTile);
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
						SDL_RenderCopy(renderer, objectTexture,NULL,&renTile);
					}
				}
				renTile.w = TILE_DIM;
				renTile.h = TILE_DIM;
				//find object based on id
				//lookup in vector
				//get properties and change rentile
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

