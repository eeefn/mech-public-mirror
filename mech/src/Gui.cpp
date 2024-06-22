#include "../headers/Gui.h"
#include "../headers/entities/Player.h"
#include "../headers/TextureManager.h"
#include "../headers/WindowManager.h"
#include "../headers/Editor.h"
#include "../headers/constants.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
Gui gui;

Gui::Gui() {
	//initialize our gui rectangles
	for (unsigned int i = 0; i < 8; i++) {
		for (unsigned int j = 0; j < 22; j++) {
			guiArr[i][j].x = j * 16;
			guiArr[i][j].y = i * 16;
			guiArr[i][j].w = 16;
			guiArr[i][j].h = 16;
		}
	}
}


void Gui::renderSoul() {
	//render the soul, with small pulse effect
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
		editor.renderEditorSelection();
	}
}

void Gui::setSoulColor(int color){
	if(color >= 0 && color <= 7){
		soulColor = color;
	}
}
