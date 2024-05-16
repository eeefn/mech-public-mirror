#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <time.h>

#include "../headers/Player.h"
#include "../headers/Collider.h"
#include "../headers/constants.h"
#include "../headers/GameObject.h"
#include "../headers/Map.h"
#include "../headers/Gui.h"
#include "../headers/Mech.h"
#include "../headers/Camera.h"
#include "../headers/controller/InputFactory.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::vector;

//int selOffY, selOffX = 0;
short texSelX, texSelY = 0;
int gameMode = PLAY;
int debug = 0;
int tilesPerWindowWidth;
int tilesPerWindowHeight;
int lastFrameTime = 0;
bool gameIsRunning = false;

const Uint8* keyPtr;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

//Rects for rendering tiles, objects and the player to

SDL_Rect renTile;

vector<Entity*> entityList;
//textures for 
SDL_Texture* tile_texture;
SDL_Texture* spriteTexture;
SDL_Texture* gameObjectTexture;
//this is the spriteSelect for animations. Currently 1*15 because only jump exists
SDL_Rect playerAnim[4][15];


int initializeWindow() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL\n");
		return FALSE;
	}
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_BORDERLESS
	);
	if (!window) {
		fprintf(stderr, "Error initializing window\n");
		return FALSE;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		fprintf(stderr, "Error initializing renderer\n");
		return FALSE;
	}
	return TRUE;
}

void setup() {
	/*setting up the display of our tiles. Find the height and width of current display. 
	use that to determine how many tiles should go in the width and the height by doing ceiling of integer division.
	tilesPerWindowWidth is cieling((pixels of width)/(width of tile)) */
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0,&dm);

	keyPtr = SDL_GetKeyboardState(NULL);
	//eventually these three will be merged into an atlas
	/*create surface  for tilemap and give it to the renderer
	----------------------------------------------------------*/
	SDL_Surface* tileMapSurface = SDL_LoadBMP("./resources/tile4.bmp");
	if (!tileMapSurface) {
		fprintf(stderr, "could not find tile images");
		return;
	}
	tile_texture = SDL_CreateTextureFromSurface(renderer, tileMapSurface);
	SDL_FreeSurface(tileMapSurface);
	
	/*create surface from spriteSheet and turn it into a texture*/
	SDL_Surface* spriteSheetSurface = SDL_LoadBMP("./resources/mushBoyJ.bmp");
	if (!spriteSheetSurface) {
		fprintf(stderr, "could not find spritesheet");
		return;
	}
	spriteTexture = SDL_CreateTextureFromSurface(renderer, spriteSheetSurface);
	SDL_FreeSurface(spriteSheetSurface);
	
	/*create surface from gameObjects and give it to renderer*/
	SDL_Surface* gameObjectSurface = SDL_LoadBMP("./resources/objSheetv1.bmp");
	if (!gameObjectSurface) {
		fprintf(stderr, "could not find gameObject texture");
		return;
	}
	gameObjectTexture = SDL_CreateTextureFromSurface(renderer, gameObjectSurface);
	camera.initializeCamera(dm.h,dm.w,renderer,tile_texture,gameObjectTexture);
	/*create surface from gui and give it to renderer*/
	SDL_Surface* guiSurface = SDL_LoadBMP("./resources/gui.bmp");
	if (!guiSurface) {
		fprintf(stderr, "could not find gui image");
		return;
	}
	gui.guiTex = SDL_CreateTextureFromSurface(renderer, guiSurface);
	/*create surface from mech and give it to renderer*/
	SDL_Surface* mechSurface = SDL_LoadBMP("./resources/mech.bmp");
	if (!mechSurface) {
		fprintf(stderr, "could not find mech image");
		return;
	}
	mech.mechTex = SDL_CreateTextureFromSurface(renderer, mechSurface);
	SDL_Surface* mechAtSurface = SDL_LoadBMP("./resources/handAt.bmp");
	if (!mechAtSurface) {
		fprintf(stderr, "could not find hands");
		return;
	}
	mech.mechAttatchmentTex = SDL_CreateTextureFromSurface(renderer, mechAtSurface);

	//instantiate the map
	map.read("lvl1Test.bin");
	map.tileMap[24][20] = -1;
	map.initGameObject();
	//cout << map.gameObjList.at(0)->xTile << '\n';

	//this is probably important
	srand(time(NULL));
	//populate the tiles from map data
	
	//create a grid of rectangles representing the animations from player spritesheet
	for (unsigned int i = 0; i < 15; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			playerAnim[j][i].x = i * 32;
			playerAnim[j][i].y = j*48;
			playerAnim[j][i].w = 32;
			playerAnim[j][i].h = 48;
		}
		
	}	

	//initialize the rect select for gameobject textures

	//setup our entitys
	Entity* pptr = &player;
	Entity* mptr = &mech;
	entityList.push_back(pptr);
	entityList.push_back(mptr);

}

void processInput() {
	SDL_Event event;
	SDL_PollEvent(&event);
	InputFactory inputFactory = InputFactory(&event,&camera.xOffset,&camera.yOffset,&gameMode,&entityList,&player.displayRect);
	gameIsRunning = inputFactory.processInput();
}

void update() {
	//fixed timestep 
	int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - lastFrameTime);
	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
		SDL_Delay(timeToWait);
	}
	
	float deltaTime = (SDL_GetTicks() - lastFrameTime) / 1000.0f;

	lastFrameTime = SDL_GetTicks();
	//update player physics if we are not editing the map
	if (gameMode == PLAY) {
		player.updateEntity(deltaTime);
		mech.updateEntity(deltaTime,camera.yOffset,camera.xOffset,player.posX,player.posY);
		if (collider.collisionCheck(mech.posX, mech.posY, MECH_WIDTH, MECH_HEIGHT, mech.velY, mech.velX, map.tileMap,camera.xOffset,camera.yOffset)) {
			mech.processCollision(collider.colResults);
		}
		//update the offset of the camera based on the entity that the target is currently following. 
		auto cameraTarget = entityList.at(0);
		camera.xOffset = (cameraTarget->posX) / TILE_DIM - (WINDOW_WIDTH / 2 - cameraTarget->entityWidth / 2) / TILE_DIM;
		camera.yOffset = (cameraTarget->posY) / TILE_DIM - (WINDOW_HEIGHT / 2 - cameraTarget->entityHeight / 2) / TILE_DIM;

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
		if (collider.collisionCheck(player.posX, player.posY, PLAYER_WIDTH, PLAYER_HEIGHT, player.velY, player.velX, map.tileMap, camera.xOffset, camera.yOffset)) {
			player.processCollision(collider.colResults);
		}
		if (abs(player.posX - mech.posX) > 60) {
			mech.highlighted = false;
		}
		else {
			mech.highlighted = true;
		}
	}
}

void render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	//iterate through the tiles we currently want to render. Im saying <= so there should be 1 extra tile
	//to play with in both height and width
	camera.renderMap(entityList.at(0));

	//editor and gameplay
	if (gameMode == EDIT) {
		//render selection window for editor.
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &gui.selWindowRen);
	}
	else {
		mech.renderMech(renderer);
		//render player
		if (player.isPlayer) {
			SDL_RenderCopy(renderer, spriteTexture, &playerAnim[player.curAnim][player.playFrame], &player.displayRect);
		}
		//render gui
		gui.renderSoul(renderer);
	}
	SDL_RenderPresent(renderer);
}

void destroyWindow() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	gameIsRunning = initializeWindow();
	setup(); 
	
	while (gameIsRunning) {
		processInput();
		update();
		render();
	}
	destroyWindow();
	std::cout << "Goodbye";
	return 0;
}