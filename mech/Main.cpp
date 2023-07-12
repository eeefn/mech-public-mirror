#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <time.h>
#include "./Player.h"
#include "./Collider.h"
#include "./constants.h"
#include "./GameObject.h"
#include "./Map.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>


using std::cout;
using std::vector;
/*
weekend notes:

*/
short selectColor = 0;
int selOffY, selOffX = 0;
short texSelX, texSelY = 0;
int gameMode = 0;
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
SDL_Rect objRen;
SDL_Rect selWindowRen;
SDL_Rect spriteDest;
SDL_Rect renTile;

short tileMap2[MAX_LVL_HEIGHT][MAX_LVL_WIDTH];
vector<GameObject> objList;
//textures for 
SDL_Texture* tile_texture;
SDL_Texture* spriteTexture;
//this is the spriteSelect for animations. Currently 1*15 because only jump exists
SDL_Rect playerAnim[4][15];



void readMap2(std::string mapIn) {
	std::ifstream map(mapIn, std::ios::in | std::ios::binary);
	for (unsigned int i = 0; i < MAX_LVL_HEIGHT; i++) {
		for (unsigned int j = 0; j < MAX_LVL_WIDTH; j++){
			map.read((char*)&tileMap2[i][j], sizeof(short));
		}
	}
}

void editMapFill() {
	
	for (int i = selWindowRen.y / TILE_DIM + yOffset; i < (selWindowRen.h / TILE_DIM) + (selWindowRen.y / TILE_DIM + yOffset) ; i++) {
		for (int j = selWindowRen.x / TILE_DIM + xOffset; j < (selWindowRen.w / TILE_DIM) + (selWindowRen.x / TILE_DIM + xOffset) ; j++) {
			cout << "i is: " << i << ". j is: " << j << '\n';
			tileMap2[i][j] = selectColor;
		}
	}
}

void saveMap(std::string mapIn) {
	std::ofstream file(mapIn, std::ios::trunc | std::ios::out | std::ios::binary);
	for (unsigned int i = 0; i < MAX_LVL_HEIGHT; i++) {
		for (unsigned int j = 0; j < MAX_LVL_WIDTH; j++) {
			file.write((char*)&tileMap2[i][j], sizeof(short));
		}
	}
}

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

	/*create surface  for tilemap and give it to the renderer
	----------------------------------------------------------*/
	SDL_Surface* tileMapSurface = SDL_LoadBMP("tile4.bmp");
	if (!tileMapSurface) {
		fprintf(stderr, "could not find image");
		return;
	}
	tile_texture = SDL_CreateTextureFromSurface(renderer, tileMapSurface);
	SDL_FreeSurface(tileMapSurface);

	/*create surface from spriteSheet and turn it into a texture*/
	SDL_Surface* spriteSheetSurface = SDL_LoadBMP("mushBoyJ.bmp");
	if (!spriteSheetSurface) {
		fprintf(stderr, "could not find spritesheet");
		return;
	}
	spriteTexture = SDL_CreateTextureFromSurface(renderer, spriteSheetSurface);
	SDL_FreeSurface(spriteSheetSurface);
	//instantiate the player, collider, and the map
	Player* player = new Player();
	Collider* collider = new Collider();
	Map* map = new Map("lvl1Test.bin");
	//this is probably important
	srand(time(NULL));
	//populate the tiles from map data
	
	readMap2("lvl1Test.bin");

	//create a grid of rectangles representing the textures in the tileMap.
	for (unsigned int i = 0; i < TILE_WIDTH_IN_TILE_MAP; i++) {
		for (unsigned int j = 0; j < TILE_WIDTH_IN_TILE_MAP; j++) {
			//cout << "tile i: " << i << "j: " << j << '\n';
			tileSelect[i][j].x = TEX_DIM * j;
			tileSelect[i][j].y = TEX_DIM * i;
			//cout << "x assigned to " << tileSelect[i][j].x << '\n';
			//cout << "y assigned to " << tileSelect[i][j].y << '\n';
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
}

void processInput() {
	SDL_Event event;
	SDL_PollEvent(&event);
	//some of this should go in an editor class. this is temp for sure
	if (gameMode == 1) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_e: gameMode = 0; break;
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
			case SDLK_f: editMapFill(); break;
			case SDLK_z: saveMap("lvl1Test.bin"); break;
			case SDLK_ESCAPE: gameIsRunning = false; break;

			}
		}
		else if (event.type == SDL_QUIT) {
			gameIsRunning = false;
		}
	}
	else {
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
			switch (event.key.keysym.sym) {
			case SDLK_w:
				if (!player.inAir) {
						//adjust player velocity to initiate jump
					player.velY -= player.playerJumpAcc;
						//change animation to jumping. The reason frame is set to -1 is 
						//player update increments current frame right after this assignment, resulting
						//in the 0th frame being played
					player.curAnim = JUMP_ANIM;
					player.playFrame = -1;
					player.inAir = true;
				}
				break;
			case SDLK_a:
				player.velX -= player.playerSpeedX;
				player.curAnim = RUN_L_ANIM;
				player.playFrame = -1;
				break;
			case SDLK_d:
				player.velX += player.playerSpeedX;
				player.curAnim = RUN_R_ANIM;
				player.playFrame = -1;
				break;
			case SDLK_e: 
				gameMode = 1; 
				//setup selector
				selWindowRen.h = TILE_DIM;
				selWindowRen.w = TILE_DIM;
				selWindowRen.x = selOffX - (spriteDest.x % TILE_DIM);
				selWindowRen.y = selOffY - (spriteDest.y % TILE_DIM);
				break;
			case SDLK_ESCAPE: gameIsRunning = FALSE; break;
			}
		}
		if (event.type == SDL_KEYUP && event.key.repeat == 0) {
			switch (event.key.keysym.sym) {
				//case SDLK_w: player.velY += player.playerJumpY; break;
				//case SDLK_s: player.velY -= player.playerSpeedY; break;
			case SDLK_a:
				player.velX += player.playerSpeedX;
				player.curAnim = IDLE_ANIM;
				player.playFrame = -1;
				break;
			case SDLK_d:
				player.velX -= player.playerSpeedX;
				player.curAnim = IDLE_ANIM;
				player.playFrame = -1;
				break;
			}
		}
		else if (event.type == SDL_QUIT) {
			gameIsRunning = FALSE;
		}
	}
	
	/*
	switch (event.type)
	{
	case SDL_QUIT:
		gameIsRunning = FALSE;
		break;
	case SDL_KEYDOWN:
		if (gameMode == 1) 
			//controls for changing selection size
			if (event.key.keysym.sym == SDLK_d) {
				selWindow.w += TILE_DIM;
			}
			if (event.key.keysym.sym == SDLK_a) {
				selWindow.w -= TILE_DIM;
				if (selWindow.w < TILE_DIM) {
					selWindow.w = TILE_DIM;
				}
			}
			if (event.key.keysym.sym == SDLK_s) {
				selWindow.h += TILE_DIM;
			}
			if (event.key.keysym.sym == SDLK_w) {
				selWindow.h -= TILE_DIM;
				if (selWindow.h < TILE_DIM) {
					selWindow.h = TILE_DIM;
				}
			}
			if (event.key.keysym.sym == SDLK_RIGHT) {
				selWindow.x += TILE_DIM;
			}
			if (event.key.keysym.sym == SDLK_LEFT) {
				selWindow.x -= TILE_DIM;
			}
			if (event.key.keysym.sym == SDLK_DOWN) {
				selWindow.y += TILE_DIM;
				if (selWindow.y >= WINDOW_HEIGHT) {
					if (yOffset < MAX_LVL_HEIGHT) {
						yOffset++;
					}
					selWindow.y -= TILE_DIM;
				}
				
			}
			if (event.key.keysym.sym == SDLK_UP) {
				selWindow.y -= TILE_DIM;
				//corner cases, first check for upward screen boundary
				if (selWindow.y <= 0) {
					//then check for map boundary
					if (yOffset > 0) {
						yOffset--;
					}
					selWindow.y = 0;
				}
			}
			if (event.key.keysym.sym == SDLK_f) {
				editMapFill();
			}
			if (event.key.keysym.sym == SDLK_0) {
				selectColor = 0;
			}
			if (event.key.keysym.sym == SDLK_1) {
				selectColor = 1;
			}
			if (event.key.keysym.sym == SDLK_2) {
				selectColor = 2;
			}
			if (event.key.keysym.sym == SDLK_3) {
				selectColor = 3;
			}
			if (event.key.keysym.sym == SDLK_3) {
				selectColor = 3;
			}
			if (event.key.keysym.sym == SDLK_4) {
				selectColor = 4;
			}
			if (event.key.keysym.sym == SDLK_5) {
				selectColor = 5;
			}
			if (event.key.keysym.sym == SDLK_z) {
				saveMap("lvl1Test.bin");
			}
		}
		}*/
		/*
		if (event.key.keysym.sym == SDLK_RIGHT) {
			xOffset++;
			if (xOffset > MAX_LVL_WIDTH-1) {
				xOffset = MAX_LVL_WIDTH - 1;
			}
		}
		if ((event.key.keysym.sym == SDLK_LEFT) && (gameMode == 1)) {
			xOffset--;
			if (xOffset < 0) {
				xOffset = 0;
			}
		}
		if (event.key.keysym.sym == SDLK_UP) {
			yOffset--;
			if (yOffset < 0) {
				yOffset = 0;
			}
			
		}
		if (event.key.keysym.sym == SDLK_DOWN) {
			yOffset++;
			if (yOffset > MAX_LVL_HEIGHT - 1) {
				yOffset = MAX_LVL_HEIGHT - 1;
			}
		}*/
		
		//break;
	//default:
		//break;
	//}
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
	if (gameMode == 0) {
		player.updatePlayer(deltaTime);
		//update player rect to change pos
		xOffset = (player.posX) / TILE_DIM - (WINDOW_WIDTH / 2 - PLAYER_WIDTH / 2) / TILE_DIM;
		yOffset = (player.posY) / TILE_DIM - (WINDOW_HEIGHT / 2 - PLAYER_HEIGHT / 2) / TILE_DIM;
		//cout << "yOffset: " << yOffset << '\n';
		if (xOffset >= 0) {
			spriteDest.x = player.posX - (xOffset * TILE_DIM) - player.posX % TILE_DIM;
		}
		else {
			xOffset = 0;
			//cout << "S" << '\n';
			spriteDest.x = player.posX - (xOffset * TILE_DIM);
		}
		if (yOffset >= 0) {
			spriteDest.y = player.posY - (yOffset * TILE_DIM) - player.posY % TILE_DIM;
		}
		else {
			yOffset = 0;
			spriteDest.y = player.posY - (yOffset * TILE_DIM);
		}
		if (collider.collisionCheck(player.posX, player.posY, PLAYER_WIDTH, PLAYER_HEIGHT, player.velY, player.velX, tileMap2, xOffset, yOffset)) {
			player.processCollision(collider.colResults);
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
	
	if (debug < 75) {
		cout << "offsets: " << xOffset << " " << yOffset << '\n';
		cout << "max of window " << tilesPerWindowHeight + xOffset << " " << tilesPerWindowWidth + yOffset << '\n';
		cout << "playerPos: " << player.posX << " " << player.posY << '\n';
	}
	//iterate through the tiles we currently want to render. Im saying <= so there should be 1 extra tile
	//to play with in both height and width
	
	for (int y = yOffset; y <= tilesPerWindowHeight + yOffset; y++) {
		for (int x = xOffset; x <= tilesPerWindowWidth + xOffset; x++) {
			short texSel = tileMap2[y][x];
			textureSelect(texSel);
			//handle offsets in the left corner. I havent handled the right corner 0.0
			renTile.x = ((x - xOffset) * TILE_DIM);
			if (player.posX > (WINDOW_WIDTH/2 - PLAYER_WIDTH/2)) {
				renTile.x -= (player.posX % TILE_DIM);
			}
			renTile.y = ((y - yOffset) * TILE_DIM);
			if (player.posY > (WINDOW_HEIGHT/2 - PLAYER_HEIGHT/2 - 8)) {
				renTile.y -= (player.posY % TILE_DIM);
			}
			SDL_RenderCopy(renderer,tile_texture, &tileSelect[texSelY][texSelX], &renTile);

		}
	}
	//editor and gameplay
	if (gameMode == 1) {
		//render selection window for editor.
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &selWindowRen);
	}
	else {
		//render player
		SDL_RenderCopy(renderer, spriteTexture, &playerAnim[player.curAnim][player.playFrame], &spriteDest);
	}
	SDL_RenderPresent(renderer);
}

void destroyWindow() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}



int main(int argc, char* args[]) {
	
	gameIsRunning = initializeWindow();
	setup(); 
	
	while (gameIsRunning) {
		processInput();
		update();
		render();
	}
	destroyWindow();

	return 0;
}