#include "../headers/Gui.h"
#include "../headers/TextureManager.h"
#include "../headers/WindowManager.h"
#include "../headers/Editor.h"
#include "../headers/constants.h"
#include "../headers/PlayerState.h"

#include <iostream>

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
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 10; j++){
			if(playerState.inventory[i][j] != nullptr){
				SDL_Rect* itemTexturePos = playerState.inventory[i][j]->getSpriteSheetPos();
				itemPos.x = getItemXPos(j);
				itemPos.y = getItemYPos(i);
				SDL_RenderCopy(windowManager.renderer,textureManager.itemsTexture,itemTexturePos,&itemPos);
			}
		}
	}
	if(heldItem != nullptr){
		SDL_Rect* itemTexturePos = heldItem->getSpriteSheetPos();
		SDL_GetMouseState(&heldItem->itemPos.x,&heldItem->itemPos.y);
		heldItem->itemPos.x -= (inventoryScale * 16) / 2;
		heldItem->itemPos.y -= (inventoryScale * 16) / 2;
		SDL_RenderCopy(windowManager.renderer,textureManager.itemsTexture,itemTexturePos,&heldItem->itemPos);
	}
}

int Gui::getItemXPos(int xInvenPos){
	int firstItemPos = inventoryPos.x + 10 * inventoryScale;
	int itemOffset = xInvenPos * ((2 + 16) * inventoryScale);
	return firstItemPos + itemOffset;	
}

int Gui::getItemYPos(int yInvenPos){
	int firstItemPos = inventoryPos.y + 10 * inventoryScale;
	int itemOffset = 0;
	if(yInvenPos != 0){
		firstItemPos += ((5 + 16) * inventoryScale);
		itemOffset = (yInvenPos - 1) * ((16 + 2) * inventoryScale);
	}
	return firstItemPos + itemOffset;	
}

int Gui::getInvPosFromXPos(int xPos){
	if(xPos >= (inventoryPos.x + 10 * inventoryScale) && xPos <= inventoryPos.x + inventoryPos.w - (10 * inventoryScale)){
		//adjust xPos to account for pos of gui and frame
		xPos = xPos - inventoryPos.x - (10 * inventoryScale);
		int clickBoxWidth = ((16 + 2) * inventoryScale);
		int invPos = xPos / clickBoxWidth;
		return invPos;
	}
	else{
		return -1;
	}
}

int Gui::getInvPosFromYPos(int yPos){
	if(yPos >= (inventoryPos.y + 10 * inventoryScale) && yPos <= inventoryPos.y + inventoryPos.h - (10 * inventoryScale)){
		yPos = yPos - inventoryPos.y - (10 * inventoryScale);
		int clickBoxHeight = ((16 + 2) * inventoryScale);
		int invPos = yPos / clickBoxHeight;
		return invPos;
	}
	else{
		return -1;
	}
}

void Gui::handleGuiClick(int xPos, int yPos){
	int xSlot = getInvPosFromXPos(xPos);
	int ySlot = getInvPosFromYPos(yPos);
	Item* itemAtClick = playerState.inventory[ySlot][xSlot];
	if(ySlot != -1 && xSlot != -1){
		if(!heldItem){
			std::cout << xSlot << " " << ySlot << std::flush;
			if(itemAtClick != nullptr){
				heldItem = itemAtClick;
				playerState.inventory[ySlot][xSlot] = nullptr;
				heldItem->itemPos = {xPos,yPos,16*inventoryScale,16*inventoryScale};
			}
		}
		else{
			if(itemAtClick == nullptr){
				playerState.inventory[ySlot][xSlot] = heldItem;
				heldItem = nullptr;
			}
		}
	}
}