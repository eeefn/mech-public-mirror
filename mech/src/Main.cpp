#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <time.h>

#include "../headers/entities/EntityManager.h"
#include "../headers/TextureManager.h"
#include "../headers/constants.h"
#include "../headers/Map.h"
#include "../headers/Gui.h"
#include "../headers/Camera.h"

#include "../headers/controller/InputFactory.h"

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

using std::cout;

int gameMode = PLAY;
int lastFrameTime = 0;
bool gameIsRunning = false;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

//Rects for rendering tiles, objects and the player to
SDL_Rect renTile;

bool initializeWindow() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL\n");
		return false;
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
		return false;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		fprintf(stderr, "Error initializing renderer\n");
		return false;
	}
	return true;
}

void setup() {
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0,&dm);

	textureManager.initPermanentTextures(renderer);
	camera.initializeCamera(dm.h,dm.w,renderer,textureManager.tileTexture,textureManager.gameObjectTexture);
	map.initialize();

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
	//reset renderer
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	camera.renderMap();

	//editor and gameplay
	if (gameMode == EDIT) {
		//render selection window for editor.
		gui.renderEditorSelection(renderer);
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