#include "./headers/Gui.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "./headers/Player.h"
Gui gui;

Gui::Gui() {
	//std::cout << "constructing gui" << '\n';
	soulColor = 0;
	pulseCount = 0;
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

void Gui::renderSoul(SDL_Renderer* rend) {
	pulseCount++;
	int fullness = player.soul / 5;
	//std::cout << "soul " << player.soul << '\n';
	fullness = (fullness - 20) * -1;
	//std::cout << "fullness " << fullness << '\n';
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
	SDL_RenderCopy(rend, gui.guiTex, &gui.guiArr[soulColor][fullness], &gui.guiComponent);
}
