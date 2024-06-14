#include "../headers/Gui.h"
#include "../headers/entities/Player.h"
#include "../headers/TextureManager.h"
#include "../headers/WindowManager.h"
#include "../headers/constants.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
Gui gui;

Gui::Gui() {

	soulColor = 0;
	pulseCount = 0;
	selectColor = 0;
	//initialize our gui rectangles
	for (unsigned int i = 0; i < 8; i++) {
		for (unsigned int j = 0; j < 22; j++) {
			gui.guiArr[i][j].x = j * 16;
			gui.guiArr[i][j].y = i * 16;
			gui.guiArr[i][j].w = 16;
			gui.guiArr[i][j].h = 16;
		}
	}
	gui.guiComponent.x = 16;
	gui.guiComponent.y = 16;
	gui.guiComponent.w = 48;
	gui.guiComponent.h = 48;
}

void Gui::expandSelWindowLeft(){
	selWindowRen.w -= TILE_DIM;
	if (selWindowRen.w < TILE_DIM) {
		selWindowRen.w = TILE_DIM;
	}
}

void Gui::expandSelWindowRight(){
	gui.selWindowRen.w += TILE_DIM;
}

void Gui::expandSelWindowDown(){
	gui.selWindowRen.h += TILE_DIM;
}

void Gui::moveSelWindowRight(){
	gui.selWindowRen.x += TILE_DIM;
}

void Gui::moveSelWindowLeft(){
	gui.selWindowRen.x -= TILE_DIM;
	if (gui.selWindowRen.x <= 0) {
		gui.selWindowRen.x = 0;
	}

}

void Gui::expandSelWindowUp(){
	gui.selWindowRen.h -= TILE_DIM;
	if (gui.selWindowRen.h < TILE_DIM) {
		gui.selWindowRen.h = TILE_DIM;
	}
}

void Gui::moveSelWindowDown(){
	gui.selWindowRen.y += TILE_DIM;
}

void Gui::moveSelWindowUp(){
	selWindowRen.y -= TILE_DIM;
	if (gui.selWindowRen.y <= 0) {
		gui.selWindowRen.y = 0;
	}
}

SDL_Rect* Gui::getSelWindowRen(){
	return &gui.selWindowRen;
}

void Gui::setupSelector(Entity* playerEntity){
	selWindowRen.h = TILE_DIM;
	selWindowRen.w = TILE_DIM;
	selWindowRen.x = (playerEntity->displayRect.x % TILE_DIM);
	selWindowRen.y = /*selOffY - */(playerEntity->displayRect.y % TILE_DIM);

}
void Gui::renderEditorSelection(){
	SDL_SetRenderDrawColor(windowManager.renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(windowManager.renderer, &gui.selWindowRen);
}

void Gui::renderSoul() {
	pulseCount++;
	int fullness = player.soul / 5;
	fullness = (fullness - 20) * -1;
	if (fullness > 21) {
		fullness = 21;
	}
	if (fullness < 0) {
		fullness = 0;
	}
	if (pulseCount > 60 && fullness < 21) {
		fullness++;
	}
	if (pulseCount > 75) {
		pulseCount = 0;
	}
	SDL_RenderCopy(windowManager.renderer, textureManager.guiTexture, &gui.guiArr[soulColor][fullness], &gui.guiComponent);
}
void Gui::render(int gameMode){
	if(gameMode == PLAY){
		renderSoul();
	}
	else{
		renderEditorSelection();
	}
}
