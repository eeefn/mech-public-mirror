#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "./constants.h"
#include <time.h>
#include <fstream>
#include <iostream>
#include <string>
#include "./Player.h"
#include "./Collider.h"

/*
weekend notes:
--> see if we can do the controls in a better way
--> i think the editor mode should be a public class that keeps the state of the editing
--> note- fill does not take into account current tile positioning rn
*/
short selectColor = 0;
//int debugCount = 0;
int tilesPerWindowWidth;
int tilesPerWindowHeight;
int gameIsRunning = FALSE;
SDL_Rect tileSelect[TILE_WIDTH_IN_TILE_MAP][TILE_WIDTH_IN_TILE_MAP];
int lastFrameTime = 0;
static int xOffset, yOffset = 0;
static int editYOffset, editXOffset = 0;
const Uint8* keyPtr;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect tile[WINDOW_HEIGHT/TILE_DIM][WINDOW_WIDTH/TILE_DIM]; 
SDL_Rect selWindow;
short tileMap2[MAX_LVL_HEIGHT][MAX_LVL_WIDTH];
SDL_Texture* tile_texture;
SDL_Texture* spriteTexture;
//this is the spriteSelect for animations. Currently 1*15 because only jump exists
SDL_Rect playerAnim[4][15];
//destination for the player
SDL_Rect spriteDest;
int gameMode = 0;
using std::cout;
int selOffY, selOffX = 0;


void readMap2(std::string mapIn) {
	std::ifstream map(mapIn, std::ios::in | std::ios::binary);
	for (unsigned int i = 0; i < MAX_LVL_HEIGHT; i++) {
		for (unsigned int j = 0; j < MAX_LVL_WIDTH; j++){
			map.read((char*)&tileMap2[i][j], sizeof(short));
		}
	}
}

void editMapFill() {
	cout << "map fill" << '\n';
	cout << "selWindow stats" << '\n';
	cout << "y: " << selWindow.y / TILE_DIM << '\n';
	cout << "x: " << selWindow.x / TILE_DIM << '\n';
	cout << "w: " << selWindow.w / TILE_DIM << '\n';
	cout << "h: " << selWindow.h / TILE_DIM << '\n';
	for (int i = selWindow.y / TILE_DIM; i < (selWindow.h / TILE_DIM) + (selWindow.y / TILE_DIM) ; i++) {
		for (int j = selWindow.x / TILE_DIM; j < (selWindow.w / TILE_DIM) + (selWindow.x / TILE_DIM) ; j++) {
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

//TODO: make this function accept txt
/*
void readMap() {
	std::ifstream file;
	file.open("lvl.txt",std::ifstream::in);
	if (!file.is_open()) {
		fprintf(stderr, "error reading level file");
		return;
	}
	std::string inStr;
	int i = 0;
	while (std::getline(file,inStr)) {
		//cout << inStr << '\n';
		for (unsigned int j = 0; j < inStr.length(); j++) {
			tileMap[i][j] = inStr[j] - 48;
		}
		i++;
	}
	file.close();
	i = 0;
	for (i; i < 75;i++) {
		for (int j = 0; j < 75;j++) {
			cout << tileMap[i][j];
		}
		cout << '\n';
	}
}
*/

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
	//instantiate the player and the colliser
	Player* player = new Player();
	Collider* collider = new Collider();
	//this is probably important
	srand(time(NULL));
	//populate the tiles from map data

	readMap2("lvl1Test.bin");
	//this section creates an array of of rectangles. Indexed to cover the screen 
	for (int i = 0; i < tilesPerWindowHeight; i++) {
		for (int j = 0; j < tilesPerWindowWidth; j++) {
			tile[i][j].x = j * TILE_DIM; //swapped as i is height
			tile[i][j].y = i * TILE_DIM; 
			tile[i][j].w = TILE_DIM;
			tile[i][j].h = TILE_DIM;
		}
	}
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
	for (unsigned int i = 0; i < 15; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			playerAnim[j][i].x = i * 32;
			playerAnim[j][i].y = j*48;
			playerAnim[j][i].w = 32;
			playerAnim[j][i].h = 48;
		}
		
	}
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
			case SDLK_RIGHT: selWindow.w += TILE_DIM; break;
			case SDLK_LEFT:
				selWindow.w -= TILE_DIM;
				if (selWindow.w < TILE_DIM) {
					selWindow.w = TILE_DIM;
				}
				break;
			case SDLK_DOWN: selWindow.h += TILE_DIM; break;
			case SDLK_UP:
				selWindow.h -= TILE_DIM;
				if (selWindow.h < TILE_DIM) {
					selWindow.h = TILE_DIM;
				}
				break;
			case SDLK_a: 
				selWindow.x -= TILE_DIM;
				if (selWindow.x <= 0) {
					selWindow.x = 0;
				}
				break;
			case SDLK_d: selWindow.x += TILE_DIM; break;
			case SDLK_s: selWindow.y += TILE_DIM; break;
			case SDLK_w: 
				selWindow.y -= TILE_DIM;
				if (selWindow.y <= 0) {
					selWindow.y = 0;
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
				selWindow.h = TILE_DIM;
				selWindow.w = TILE_DIM;
				selWindow.x = selOffX;
				selWindow.y = selOffY;
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

		if (collider.collisionCheck(player.posX, player.posY, PLAYER_WIDTH, PLAYER_HEIGHT, player.velY, player.velX, tileMap2)) {
			player.processCollision(collider.colResults, tile);
		}
		//update player rect to change pos
		spriteDest.x = player.posX;
		spriteDest.y = player.posY;
	}
}

void render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//traverse the map
	for (int i = 0; i < tilesPerWindowHeight; i++) {
		for (int j = 0; j < tilesPerWindowWidth; j++) {
			int textureNum = tileMap2[i + yOffset][j + xOffset];
			int x, y;
			if (textureNum > (TILE_WIDTH_IN_TILE_MAP - 1)) {
				x = ((textureNum + 1)%TILE_WIDTH_IN_TILE_MAP) - 1;
				y = ((textureNum + 1) / TILE_WIDTH_IN_TILE_MAP);
			}
			else {
				x = textureNum;
				y = 0;
			}
			SDL_RenderCopy(renderer, tile_texture, &tileSelect[y][x], &tile[i][j]);
		}
	}
	//editor and gameplay
	if (gameMode == 1) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &selWindow);
	}
	else {
		//cout << "should be rendering the player" << '\n';
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