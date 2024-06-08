#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <time.h>

#include "../headers/entities/Mech.h"
#include "../headers/entities/Player.h"
#include "../headers/entities/EntityManager.h"
#include "../headers/TextureManager.h"
#include "../headers/Collider.h"
#include "../headers/constants.h"
#include "../headers/GameObject.h"
#include "../headers/Map.h"
#include "../headers/Gui.h"
#include "../headers/Camera.h"

#include "../headers/controller/InputFactory.h"

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

using std::cout;

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
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0,&dm);

	keyPtr = SDL_GetKeyboardState(NULL);
	//eventually these three will be merged into an atlas
	/*create surface  for tilemap and give it to the renderer
	----------------------------------------------------------*/
	textureManager.initPermanentTextures(renderer);
	/*create surface from gameObjects and give it to renderer*/
	camera.initializeCamera(dm.h,dm.w,renderer,textureManager.tileTexture,textureManager.gameObjectTexture);
	player.initializeSpriteTexture(renderer);

	//instantiate the map
	map.read("lvl1Test.bin");
	map.tileMap[24][20] = -1;
	map.initGameObject();

	//this is probably important
	srand(time(NULL));

}

void processInput() {
	SDL_Event event;
	SDL_PollEvent(&event);
	InputFactory inputFactory = InputFactory(&event, &gameMode);
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
		entityManager.update(deltaTime);
		camera.update();
	}
}

void render() {

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	camera.renderMap();

	//editor and gameplay
	if (gameMode == EDIT) {
		//render selection window for editor.
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &gui.selWindowRen);
	}
	else {
		//render all entities
		entityManager.render(renderer);
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