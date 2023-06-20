#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "./constants.h"
#include <time.h>
#include <fstream>
#include <iostream>
#include<string>

int tilesPerWindowWidth;
int tilesPerWindowHeight;
int gameIsRunning = FALSE;
int lastFrameTime = 0;
static int xOffset = 0;
static int yOffset = 0;
const Uint8* keyPtr;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect selectT1;
SDL_Rect selectT2;
SDL_Rect selectT3;
SDL_Rect selectT4;
SDL_Rect tile[45][80]; //dependent on window size. This should be retroffitted at some point. 
int tileMap[MAX_LVL_HEIGHT][MAX_LVL_WIDTH];
SDL_Texture* tile_texture;
using std::cout;

struct ball {
	float x;
	float y;
	float width;
	float height;
}ball;

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

	cout << "width= " << tilesPerWindowWidth << '\n';
	cout << "height= " << tilesPerWindowHeight << '\n';
	keyPtr = SDL_GetKeyboardState(NULL);
	ball.x = 40;
	ball.y = 40;
	ball.width = 15;
	ball.height = 15;
	SDL_Surface* tileMapSurface = SDL_LoadBMP("tile3.bmp");
	if (!tileMapSurface) {
		fprintf(stderr, "could not find image");
		return;
	}
	tile_texture = SDL_CreateTextureFromSurface(renderer, tileMapSurface);
	SDL_FreeSurface(tileMapSurface);
	srand(time(NULL));
	readMap();
	for (int i = 0; i < tilesPerWindowHeight; i++) {
		for (int j = 0; j < tilesPerWindowWidth; j++) {
			tile[i][j].x = j * 16; //swapped as i is height
			tile[i][j].y = i * 16; 
			tile[i][j].w = 16;
			tile[i][j].h = 16;
		}
	}
	selectT1.x = 0;
	selectT1.y = 0;
	selectT1.w = 16;
	selectT1.h = 16;

	selectT2.x = 16;
	selectT2.y = 0;
	selectT2.w = 16;
	selectT2.h = 16;

	selectT3.x = 32;
	selectT3.y = 0;
	selectT3.w = 16;
	selectT3.h = 16;

	selectT4.x = 48;
	selectT4.y = 0;
	selectT4.w = 16;
	selectT4.h = 16;
}

void processInput() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		gameIsRunning = FALSE;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			gameIsRunning = FALSE;
		}
		if (event.key.keysym.sym == SDLK_RIGHT) {
			xOffset++;
			if (xOffset > MAX_LVL_WIDTH-1) {
				xOffset = MAX_LVL_WIDTH - 1;
			}
		}
		if (event.key.keysym.sym == SDLK_LEFT) {
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
		}
		break;
	default:
		break;
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
	//ball.x += 50 * deltaTime;
	//ball.y += 20 * deltaTime;
}

void render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_Rect ball_rect = {
		(int)ball.x,
		(int)ball.y,
		(int)ball.width,
		(int)ball.height
	};

	for (int i = 0; i < tilesPerWindowHeight; i++) {
		for (int j = 0; j < tilesPerWindowWidth; j++) {
			switch (tileMap[i + yOffset][j + xOffset]) {
			case 1:
				SDL_RenderCopy(renderer,tile_texture,&selectT1,&tile[i][j]);
				break;
			case 2:
				SDL_RenderCopy(renderer, tile_texture, &selectT2, &tile[i][j]);
				break;
			case 3:
				SDL_RenderCopy(renderer, tile_texture, &selectT3, &tile[i][j]);
				break;
			case 4:
				SDL_RenderCopy(renderer, tile_texture, &selectT4, &tile[i][j]);
				break;
			}
		}
	}
	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	//SDL_RenderFillRect(renderer, &ball_rect);
	SDL_RenderPresent(renderer);
}

void destroyWindow() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* args[]) {
	
	gameIsRunning = initializeWindow();
	//readMap();
	setup(); 
	
	while (gameIsRunning) {
		processInput();
		update();
		render();
	}
	destroyWindow();

	return 0;
}