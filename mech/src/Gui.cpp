#include "../headers/Gui.h"
#include "../headers/TextureManager.h"
#include "../headers/WindowManager.h"
#include "../headers/Editor.h"
#include "../headers/constants.h"
#include "../headers/PlayerState.h"

Gui gui;

Gui::Gui() {
	//initialize our gui rectangles
	initializeInventory();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 22; j++) {
			guiArr[i][j] = {j*16,i*16,16,16};
		}
	}
}


void Gui::initializeInventory(){
	int inventoryWidth = 198 * inventoryScale;
	int inventoryHeight = 75 * inventoryScale;
	int inventoryYPos = (windowSize.WINDOW_HEIGHT - inventoryHeight) / 2;
	int inventoryXPos = (windowSize.WINDOW_WIDTH - inventoryWidth) / 2;
	inventoryPos = {inventoryXPos,inventoryYPos,inventoryWidth,inventoryHeight};
}

void Gui::renderSoul() {
	//render the soul, with small pulse effect
	pulseCount++;
	//TODO reintegrate player soul and gui soul effect
	int fullness = playerState.soul / 5;
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
	SDL_RenderCopy(windowManager.renderer, textureManager.guiTexture, &gui.guiArr[playerState.soulColor][fullness], &gui.guiComponent);
}

void Gui::render(int gameMode){
	if(gameMode == gamemodes.PLAY){
		renderSoul();
		if(playerState.inventoryOpen){
			renderInventory();//render inventory	
		}
	}
	else{
		editor.renderEditorSelection();
	}
}



void Gui::renderInventory(){
	SDL_RenderCopy(windowManager.renderer,textureManager.inventoryTexture,NULL,&inventoryPos);
}