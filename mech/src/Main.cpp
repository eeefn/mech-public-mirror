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
#include "../headers/PlayInput.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using std::cout;
using std::vector;
/*
weekend notes:
need to make an abstraction for the camera, that allows the camera to follow a specific entity.
both mech and player will extend the entity class. 
*/
short selectColor = 0;
int selOffY, selOffX = 0;
short texSelX, texSelY = 0;
int gameMode = PLAY;
int debug = 0;
int tilesPerWindowWidth;
int tilesPerWindowHeight;
int lastFrameTime = 0;
static int xOffset, yOffset = 0;
static int editYOffset, editXOffset = 0;
bool gameIsRunning = false;

SDL_Rect tileSelect[TILE_WIDTH_IN_TILE_MAP][TILE_WIDTH_IN_TILE_MAP];

const Uint8* keyPtr;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
//Rects for rendering tiles, objects and the player to
SDL_Rect objTex;
SDL_Rect selWindowRen;
SDL_Rect spriteDest;
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
	int width = dm.w;
	int height = dm.h;
	tilesPerWindowWidth = (dm.w + TILE_DIM - 1) / TILE_DIM;
	tilesPerWindowHeight = (dm.h + TILE_DIM - 1) / TILE_DIM;

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
	

	//create a grid of rectangles representing the textures in the tileMap.
	for (unsigned int i = 0; i < TILE_WIDTH_IN_TILE_MAP; i++) {
		for (unsigned int j = 0; j < TILE_WIDTH_IN_TILE_MAP; j++) {
			tileSelect[i][j].x = TEX_DIM * j;
			tileSelect[i][j].y = TEX_DIM * i;
			tileSelect[i][j].w = TEX_DIM;
			tileSelect[i][j].h = TEX_DIM;
		}
	}
	//create a grid of rectangles representing the animations from player spritesheet
	for (unsigned int i = 0; i < 15; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			playerAnim[j][i].x = i * 32;
			playerAnim[j][i].y = j*48;
			playerAnim[j][i].w = 32;
			playerAnim[j][i].h = 48;
		}
		
	}
	//initialize the rendering rect that iterates over the screen each frame
	renTile.x = 0;
	renTile.y = 0;
	renTile.w = TILE_DIM;
	renTile.h = TILE_DIM;
	//initialize the rect that the sprite gets rendered to
	spriteDest.x = 0;
	spriteDest.y = 0;
	spriteDest.w = PLAYER_WIDTH;
	spriteDest.h = PLAYER_HEIGHT;
	//initialize the rect select for gameobject textures
	objTex.x = 0;
	objTex.y = 0;
	objTex.w = TILE_DIM;
	objTex.h = TILE_DIM;
	//setup our entitys
	Entity* pptr = &player;
	Entity* mptr = &mech;
	entityList.push_back(pptr);
	entityList.push_back(mptr);

}

void processInput() {
	SDL_Event event;
	SDL_PollEvent(&event);
	//some of this should go in an editor class. this is temp for sure
	if (gameMode == EDIT) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_e: gameMode = PLAY; break;
			case SDLK_RIGHT: selWindowRen.w += TILE_DIM; break;
			case SDLK_LEFT:
				selWindowRen.w -= TILE_DIM;
				if (selWindowRen.w < TILE_DIM) {
					selWindowRen.w = TILE_DIM;
				}
				break;
			case SDLK_DOWN: selWindowRen.h += TILE_DIM; break;
			case SDLK_UP:
				selWindowRen.h -= TILE_DIM;
				if (selWindowRen.h < TILE_DIM) {
					selWindowRen.h = TILE_DIM;
				}
				break;
			case SDLK_a: 
				selWindowRen.x -= TILE_DIM;
				if (selWindowRen.x <= 0) {
					selWindowRen.x = 0;
				}
				break;
			case SDLK_d: selWindowRen.x += TILE_DIM; break;
			case SDLK_s: selWindowRen.y += TILE_DIM; break;
			case SDLK_w: 
				selWindowRen.y -= TILE_DIM;
				if (selWindowRen.y <= 0) {
					selWindowRen.y = 0;
				}
				break;
			case SDLK_0: selectColor = 0; break;
			case SDLK_1: selectColor = 1; break;
			case SDLK_2: selectColor = 2; break;
			case SDLK_3: selectColor = 3; break;
			case SDLK_f: map.fill(selWindowRen,xOffset,yOffset,selectColor); break;
			case SDLK_z: map.save("lvl1Test.bin"); break;
			case SDLK_ESCAPE: gameIsRunning = false; break;

			}
		}
		else if (event.type == SDL_QUIT) {
			gameIsRunning = false;
		}
	}
	else {
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
			gameIsRunning = input.processKeydown(&event, &entityList);
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			input.processMousedown(&event,&entityList);
		}
		if (event.type == SDL_KEYUP && event.key.repeat == 0) {
			input.processKeyup(&event, &entityList);
		}
		else if (event.type == SDL_QUIT) {
				gameIsRunning = FALSE;
		}
	}
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
		mech.updateEntity(deltaTime,yOffset,xOffset,player.posX,player.posY);
		if (collider.collisionCheck(mech.posX, mech.posY, MECH_WIDTH, MECH_HEIGHT, mech.velY, mech.velX, map.tileMap,xOffset,yOffset)) {
			mech.processCollision(collider.colResults);
		}
		//update player rect to change pos
		xOffset = (player.posX) / TILE_DIM - (WINDOW_WIDTH / 2 - PLAYER_WIDTH / 2) / TILE_DIM;
		yOffset = (player.posY) / TILE_DIM - (WINDOW_HEIGHT / 2 - PLAYER_HEIGHT / 2) / TILE_DIM;
		if (xOffset >= 0) {
			spriteDest.x = player.posX - (xOffset * TILE_DIM) - player.posX % TILE_DIM;
		}
		else {
			xOffset = 0;
			spriteDest.x = player.posX - (xOffset * TILE_DIM);
		}
		if (yOffset >= 0) {
			spriteDest.y = player.posY - (yOffset * TILE_DIM) - player.posY % TILE_DIM;
		}
		else {
			yOffset = 0;
			spriteDest.y = player.posY - (yOffset * TILE_DIM);
		}
		if (collider.collisionCheck(player.posX, player.posY, PLAYER_WIDTH, PLAYER_HEIGHT, player.velY, player.velX, map.tileMap, xOffset, yOffset)) {
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

void textureSelect(short select) {
	if (select > (TILE_WIDTH_IN_TILE_MAP - 1)) {
		texSelX = ((select + 1) % TILE_WIDTH_IN_TILE_MAP) - 1;
		texSelY = ((select + 1) / TILE_WIDTH_IN_TILE_MAP);
	}
	else {
		texSelX = select;
		texSelY = 0;
	}
}

void render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	//iterate through the tiles we currently want to render. Im saying <= so there should be 1 extra tile
	//to play with in both height and width
	
	for (int y = yOffset; y <= tilesPerWindowHeight + yOffset; y++) {
		for (int x = xOffset; x <= tilesPerWindowWidth + xOffset; x++) {
			//grab the texture we should have for the given tile from the map
			short texSel = map.tileMap[y][x];
			renTile.x = ((x - xOffset) * TILE_DIM);
			if (player.posX > (WINDOW_WIDTH / 2 - PLAYER_WIDTH / 2)) {
				renTile.x -= (player.posX % TILE_DIM);
			}
			renTile.y = ((y - yOffset) * TILE_DIM);
			if (player.posY > (WINDOW_HEIGHT / 2 - PLAYER_HEIGHT / 2 - 8)) {
				renTile.y -= (player.posY % TILE_DIM);
			}
			if (texSel > 0) {
				textureSelect(texSel);
				//handle offsets in the left corner. I havent handled the right corner 0.0
				SDL_RenderCopy(renderer, tile_texture, &tileSelect[texSelY][texSelX], &renTile);
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
						SDL_RenderCopy(renderer, gameObjectTexture,NULL,&renTile);
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
	//editor and gameplay
	if (gameMode == EDIT) {
		//render selection window for editor.
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &selWindowRen);
	}
	else {
		mech.renderMech(renderer);
		//render player
		if (player.isPlayer) {
			SDL_RenderCopy(renderer, spriteTexture, &playerAnim[player.curAnim][player.playFrame], &spriteDest);
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
	std::cout << "Hello";
	return 0;
}