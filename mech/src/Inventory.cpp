#include "../headers/Inventory.h"
#include "../headers/items/ItemFactory.h"
#include "../headers/TextureManager.h"
#include "../headers/WindowManager.h"
#include <stdexcept>

int Inventory::inventoryScale = 3;

Inventory::Inventory(int slotsX, int slotsY, int stackLimit){
    inventorySize.slotsX = slotsX;
    inventorySize.slotsY = slotsY;
    this->stackLimit = stackLimit;
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
	renderRect.posOnScreen = {inventoryXPos,inventoryYPos,inventoryWidth,inventoryHeight};
	renderRect.posOnTexture = {0,0,198,75};
}

void Inventory::pickItem(){
	if(itemAtClick != nullptr){
		heldItem = itemAtClick;
		inventory[slotClicked.slotsY][slotClicked.slotsX] = nullptr;
		heldItem->renderRectRefs.posOnScreen = {0,0,16*inventoryScale,16*inventoryScale};
	}
}

void Inventory::pickHalf(){
	if(itemAtClick){
		int half = itemAtClick->numberOfItems / 2;
		if(half != 0){
			heldItem = itemFactory.makeItem(itemAtClick->itemType,half);
			itemAtClick->numberOfItems -= half;
			heldItem->renderRectRefs.posOnScreen = {0,0,16*inventoryScale,16*inventoryScale};
		}
	}
	return;
}

void Inventory::placeOne(){
	if(itemAtClick){
		if(itemAtClick->itemType == heldItem->itemType){
			if(itemAtClick->numberOfItems < stackLimit){
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
	}
	else{
		if(heldItem->numberOfItems > 1){
			heldItem->numberOfItems--;
			inventory[slotClicked.slotsY][slotClicked.slotsX] = itemFactory.makeItem(heldItem->itemType,1);
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
	SDL_RenderCopy(windowManager.renderer,textureManager.inventoryTexture,&renderRect.posOnTexture,&renderRect.posOnScreen);
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 10; j++){
			if(inventory.at(i).at(j) != nullptr){
				SDL_Rect* itemTexturePos = inventory.at(i).at(j)->getSpriteSheetPos();
				itemPos.x = getItemXPos(j);
				itemPos.y = getItemYPos(i);
				SDL_RenderCopy(windowManager.renderer,textureManager.itemsTexture,itemTexturePos,&itemPos);
				if(inventory[i][j]->numberOfItems > 1){
					renderNumber(inventory.at(i).at(j)->numberOfItems,itemPos.x + 2*inventoryScale,itemPos.y,windowManager.renderer);
				}
			}
		}
	}
	if(heldItem != nullptr){
		SDL_Rect* itemTexturePos = heldItem->getSpriteSheetPos();
		SDL_GetMouseState(&heldItem->renderRectRefs.posOnScreen.x,&heldItem->renderRectRefs.posOnScreen.y);
		heldItem->renderRectRefs.posOnScreen.x -= (inventoryScale * 16) / 2;
		heldItem->renderRectRefs.posOnScreen.y -= (inventoryScale * 16) / 2;
		SDL_RenderCopy(windowManager.renderer,textureManager.itemsTexture,itemTexturePos,&heldItem->renderRectRefs.posOnScreen);
		if(heldItem->numberOfItems > 1){
			renderNumber(heldItem->numberOfItems,heldItem->renderRectRefs.posOnScreen.x + 2*inventoryScale,heldItem->renderRectRefs.posOnScreen.y,windowManager.renderer);
		}
	}
}

int Inventory::getItemXPos(int xInvenPos){
	int firstItemPos = renderRect.posOnScreen.x + 10 * inventoryScale;
	int itemOffset = xInvenPos * ((2 + 16) * inventoryScale);
	return firstItemPos + itemOffset;	
}

int Inventory::getItemYPos(int yInvenPos){
	int firstItemPos = renderRect.posOnScreen.y + 10 * inventoryScale;
	int itemOffset = 0;
	if(yInvenPos != 0){
		firstItemPos += ((5 + 16) * inventoryScale);
		itemOffset = (yInvenPos - 1) * ((16 + 2) * inventoryScale);
	}
	return firstItemPos + itemOffset;	
}

int Inventory::getInvPosFromXPos(int xPos){
	if(xPos >= (renderRect.posOnScreen.x + 10 * inventoryScale) && xPos <= renderRect.posOnScreen.x + renderRect.posOnScreen.w - (10 * inventoryScale)){
		//adjust xPos to account for pos of gui and frame
		xPos = xPos - renderRect.posOnScreen.x - (10 * inventoryScale);
		int clickBoxWidth = ((16 + 2) * inventoryScale);
		int invPos = xPos / clickBoxWidth;
		if(invPos >= inventorySize.slotsX){
			invPos = inventorySize.slotsX - 1;
		}
		return invPos;
	}
	else{
		return -1;
	}
}

int Inventory::getInvPosFromYPos(int yPos){
	if(yPos >= (renderRect.posOnScreen.y + 10 * inventoryScale) && yPos <= renderRect.posOnScreen.y + renderRect.posOnScreen.h - (10 * inventoryScale)){
		yPos = yPos - renderRect.posOnScreen.y - (10 * inventoryScale);
		int clickBoxHeight = ((16 + 2) * inventoryScale);
		int invPos = yPos / clickBoxHeight;
		if(invPos >= inventorySize.slotsY){
			invPos = inventorySize.slotsY - 1;
		}
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
		if(totalItems > stackLimit){
			int remainingItems = totalItems - stackLimit;
			itemAtClick->numberOfItems = stackLimit;
			heldItem->numberOfItems = remainingItems;
		}
		else{
			itemAtClick->numberOfItems = totalItems;
			delete heldItem;
			heldItem = nullptr;
		}
	}
}

bool Inventory::addToInventory(Item* itemToAdd){
	bool addSuccess = false;
	int tempIPos = 0;
	int tempJPos = 0;
	for(int i = inventorySize.slotsY - 1; i >= 0; i--){
		for(int j = inventorySize.slotsX - 1; j >= 0; j--){
			if(!inventory[i][j]){
				addSuccess = true;
				tempIPos = i;
				tempJPos = j;
			}
			else if(inventory[i][j]->itemType == itemToAdd->itemType){
				if(inventory[i][j]->numberOfItems + itemToAdd->numberOfItems <= stackLimit){
					inventory[i][j]->numberOfItems += itemToAdd->numberOfItems;
					delete itemToAdd;
					return true;
				}
			}
		}
	}
	if(addSuccess){
		inventory[tempIPos][tempJPos] = itemToAdd;
	}
	return addSuccess;	
}

vector<Item*>* Inventory::getInventoryRow(int rowToGet){
	vector<Item*> *returnRow;
	try{
		returnRow = &inventory.at(rowToGet);
	} 
	catch(const std::out_of_range& oor){
		returnRow = nullptr;
	}
	return returnRow;
}

void Inventory::deleteFromInventory(Item* itemToDelete){
	for(int i = 0; i < inventorySize.slotsY; i++){
		for(int j = 0; j < inventorySize.slotsX;j++){
			if(inventory[i][j] == itemToDelete){
				delete itemToDelete;
				inventory[i][j] = nullptr;
			}
		}
	}
}

void Inventory::update(){
	manageDeletedItems();
}

void Inventory::manageDeletedItems(){
	for(int i = 0; i < inventorySize.slotsY; i++){
		for(int j = 0; j < inventorySize.slotsX; j++){
			Item* item = inventory[i][j];
			if(item != nullptr){
				if(item->requestDeletion){
					delete item;
					inventory[i][j] = nullptr;
				}
			}
		}
	}
}