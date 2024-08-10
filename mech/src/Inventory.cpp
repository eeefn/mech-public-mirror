#include "../headers/Inventory.h"
#include "../headers/items/ItemManager.h"
#include "../headers/TextureManager.h"
#include "../headers/WindowManager.h"
#include <iostream>
int Inventory::inventoryScale = 3;

Inventory::Inventory(int slotsX, int slotsY, int stackLimit){
    inventorySize.slotsX = slotsX;
    inventorySize.slotsY = slotsY;
    this->stackLimit = stackLimit;
	for(int i = 0; i < 10;i++){
		numArr[i] = {i * 3, 0, 3,6};
	}
    inventory.resize(slotsY);
    for(int j = 0; j < slotsY; j++){
        for(int i = 0; i < slotsX; i++){
            inventory.at(j).push_back(nullptr);
        }
    }
	initializeInventory();
    return;
}


void Inventory::initializeInventory(){
	int inventoryWidth = 198 * inventoryScale;
	int inventoryHeight = 75 * inventoryScale;
	int inventoryYPos = (windowSize.WINDOW_HEIGHT - inventoryHeight) / 2;
	int inventoryXPos = (windowSize.WINDOW_WIDTH - inventoryWidth) / 2;
	this->inventoryPos = {inventoryXPos,inventoryYPos,inventoryWidth,inventoryHeight};
}
void Inventory::pickHalf(){
	if(itemAtClick != nullptr){
		int half = itemAtClick->numberOfItems / 2;
		if(half != 0){
			heldItem = itemManager.makeItem(itemAtClick->itemType,half);
			itemAtClick->numberOfItems -= half;
			heldItem->itemPos = {0,0,16*inventoryScale,16*inventoryScale};
		}
	}
	return;
}

void Inventory::placeItem(int num){
}

void Inventory::placeOne(){
	if(itemAtClick){
			if(itemAtClick->numberOfItems < 128){
				itemAtClick->numberOfItems++;
				if(heldItem->numberOfItems > 1){
					heldItem->numberOfItems--;
				}
				else{
					delete heldItem;
					heldItem = nullptr;	
				}
			}
	}
	else{
		if(heldItem->numberOfItems > 1){
			heldItem->numberOfItems--;
			inventory[slotClicked.slotsY][slotClicked.slotsX] = itemManager.makeItem(heldItem->itemType,1);
		}
		else{
			inventory[slotClicked.slotsY][slotClicked.slotsX] = heldItem;
			heldItem = nullptr;	
		}
	}
	return;	
}

void Inventory::renderNumber(int num, int xPos, int yPos,SDL_Renderer* rend){
	SDL_Rect dispNum = {xPos,yPos,3*inventoryScale,7*inventoryScale};
	int hundredsPlace = (num / 100);
	num = num - hundredsPlace * 100;
	int tensPlace = num / 10;
	num = num - tensPlace * 10;
	int onesPlace = num;
	int distBetweenNum = 2 * inventoryScale + 3 *inventoryScale;
	if(hundredsPlace != 0){
		SDL_RenderCopy(rend,textureManager.numberTexture,&numArr[hundredsPlace], &dispNum);
		dispNum.x += distBetweenNum;
		SDL_RenderCopy(rend,textureManager.numberTexture,&numArr[tensPlace], &dispNum);
		dispNum.x += distBetweenNum;
		SDL_RenderCopy(rend,textureManager.numberTexture,&numArr[onesPlace], &dispNum);
	}
	else{
		dispNum.x += distBetweenNum;	
		if(tensPlace != 0){
			SDL_RenderCopy(rend,textureManager.numberTexture,&numArr[tensPlace], &dispNum);
			dispNum.x += distBetweenNum;
			SDL_RenderCopy(rend,textureManager.numberTexture,&numArr[onesPlace], &dispNum);
		}
		else{
			dispNum.x += distBetweenNum;
			SDL_RenderCopy(rend,textureManager.numberTexture,&numArr[onesPlace], &dispNum);
		}
	}
}

void Inventory::renderInventory(){
	SDL_RenderCopy(windowManager.renderer,textureManager.inventoryTexture,NULL,&inventoryPos);
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 10; j++){
			if(inventory.at(i).at(j) != nullptr){
				SDL_Rect* itemTexturePos = inventory.at(i).at(j)->getSpriteSheetPos();
				itemPos.x = getItemXPos(j);
				itemPos.y = getItemYPos(i);
				SDL_RenderCopy(windowManager.renderer,textureManager.itemsTexture,itemTexturePos,&itemPos);
				renderNumber(inventory.at(i).at(j)->numberOfItems,itemPos.x + 2*inventoryScale,itemPos.y,windowManager.renderer);
			}
		}
	}
	if(heldItem != nullptr){
		SDL_Rect* itemTexturePos = heldItem->getSpriteSheetPos();
		SDL_GetMouseState(&heldItem->itemPos.x,&heldItem->itemPos.y);
		heldItem->itemPos.x -= (inventoryScale * 16) / 2;
		heldItem->itemPos.y -= (inventoryScale * 16) / 2;
		SDL_RenderCopy(windowManager.renderer,textureManager.itemsTexture,itemTexturePos,&heldItem->itemPos);
		renderNumber(heldItem->numberOfItems,heldItem->itemPos.x + 2*inventoryScale,heldItem->itemPos.y,windowManager.renderer);

	}
}

int Inventory::getItemXPos(int xInvenPos){
	int firstItemPos = inventoryPos.x + 10 * inventoryScale;
	int itemOffset = xInvenPos * ((2 + 16) * inventoryScale);
	return firstItemPos + itemOffset;	
}

int Inventory::getItemYPos(int yInvenPos){
	int firstItemPos = inventoryPos.y + 10 * inventoryScale;
	int itemOffset = 0;
	if(yInvenPos != 0){
		firstItemPos += ((5 + 16) * inventoryScale);
		itemOffset = (yInvenPos - 1) * ((16 + 2) * inventoryScale);
	}
	return firstItemPos + itemOffset;	
}

int Inventory::getInvPosFromXPos(int xPos){
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

int Inventory::getInvPosFromYPos(int yPos){
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
bool Inventory::setSlotClicked(int xPosClicked,int yPosClicked){
	slotClicked = {getInvPosFromXPos(xPosClicked),getInvPosFromYPos(yPosClicked)};
	if(slotClicked.slotsX == -1 || slotClicked.slotsY == -1){ return false;}
	return true;
}
void Inventory::handleInventoryClick(int xPos, int yPos,Uint32 clickType){
	if(setSlotClicked(xPos, yPos)){
		itemAtClick =inventory[slotClicked.slotsY][slotClicked.slotsX];
		if(heldItem){
			if(clickType == SDL_BUTTON_LEFT){
				placeItem();
			}
			else if(clickType == SDL_BUTTON_RIGHT){
				placeOne();
			}
		}
		else{
			if(clickType == SDL_BUTTON_LEFT){
				pickItem();
			}
			else if(clickType == SDL_BUTTON_RIGHT){
				pickHalf();	
			}
		}
	}
}

void Inventory::placeItem(){
	if(itemAtClick == nullptr){
		inventory[slotClicked.slotsY][slotClicked.slotsX] = heldItem;
		heldItem = nullptr;
	}
	else if(itemAtClick->itemType == heldItem->itemType){
		int totalItems = itemAtClick->numberOfItems + heldItem->numberOfItems;
		if(totalItems > 128){
			int remainingItems = totalItems - 128;
			itemAtClick->numberOfItems = 128;
			heldItem->numberOfItems = remainingItems;
		}
		else{
			itemAtClick->numberOfItems = totalItems;
			delete heldItem;
			heldItem = nullptr;
		}
	}
}

void Inventory::pickItem(){
	if(itemAtClick != nullptr){
		heldItem = itemAtClick;
		inventory[slotClicked.slotsY][slotClicked.slotsX] = nullptr;
		heldItem->itemPos = {0,0,16*inventoryScale,16*inventoryScale};
	}
}

bool Inventory::addToInventory(Item* itemToAdd){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 10; j++){
			if(inventory[i][j] == nullptr){
				inventory[i][j] = itemToAdd;
				return true;
			}
		}
	}
	return false;	
}