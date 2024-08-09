#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <time.h>

#include "../headers/entities/EntityManager.h"
#include "../headers/gameObjects/GameObjectManager.h"
#include "../headers/TextureManager.h"
#include "../headers/WindowManager.h"
#include "../headers/constants.h"
#include "../headers/Map.h"
#include "../headers/Gui.h"
#include "../headers/Camera.h"

#include "../headers/PlayerState.h"
#include "../headers/items/RockItem.h"
#include "../headers/items/StickItem.h"

#include "../headers/controller/InputFactory.h"

#include <iostream>

using std::cout;

int gameMode = gamemodes.PLAY;
int lastFrameTime = 0;
bool gameIsRunning = false;

void setup() {
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0,&dm);

	textureManager.initPermanentTextures(windowManager.renderer);
	map.initialize();
	camera.initializeCamera(dm.h,dm.w,entityManager.getFrontEntity(),dm);

	Item* rock = new RockItem(128);
	Item* stick = new StickItem(128);
	playerState.addToInventory(rock);
	playerState.addToInventory(stick);
	srand(time(NULL));
}

void processInput() {
	SDL_Event event;
	//handle all events
	while(SDL_PollEvent(&event)){
		gameIsRunning = inputFactory.processInput(&event, &gameMode);
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
	if (gameMode == gamemodes.PLAY) {
		entityManager.update(deltaTime);
		camera.update();
		gameObjectManager.updateGameObjects();
	}
	inputFactory.update();
}

void render() {
	//reset renderer
	SDL_SetRenderDrawColor(windowManager.renderer, 0, 0, 0, 255);
	SDL_RenderClear(windowManager.renderer);

	camera.renderBackround();	
	gameObjectManager.renderGameObjects(windowManager.renderer);
	camera.renderMap();
	entityManager.render(gameMode);
	gui.render(gameMode);

	SDL_RenderPresent(windowManager.renderer);
}


int main(int argc, char* argv[]) {
	gameIsRunning = windowManager.initializeWindow();
	
	setup(); 
	
	while (gameIsRunning) {
		processInput();
		update();
		render();
	}

	windowManager.destroyWindow();
	std::cout << "Goodbye";
	return 0;
}