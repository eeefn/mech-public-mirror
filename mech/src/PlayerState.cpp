#include "../headers/PlayerState.h"

PlayerState playerState;

PlayerState::PlayerState(){
	playerInventory.addToInventory(itemFactory.makeItem(ItemCodes::SOULSWORD,1));
	playerInventory.addToInventory(itemFactory.makeItem(ItemCodes::SOULPICK,1));
	playerInventory.addToInventory(itemFactory.makeItem(ItemCodes::SOULSHOVEL,1));
	playerInventory.addToInventory(itemFactory.makeItem(ItemCodes::SOULAXE,1));
	playerInventory.addToInventory(itemFactory.makeItem(ItemCodes::SOULFISHINGROD,1));
}

void PlayerState::placeItemFromHotbar(){
	Item* itemToPlace = hotbar.getItemAtSelectedSlot();
	--(*itemToPlace);
	if(itemToPlace->requestDeletion){
		hotbar.decrementSelectedSlot();
	}
	else{
		hotbar.setSelectedSlot(hotbar.selectedSlot);
	}
}

void PlayerState::update(){
	playerInventory.update();
	hotbar.update();
	craftingWindow.update();
}
void PlayerState::handleInventoryClick(int xPos, int yPos,Uint32 clickType){
	if(!playerInventory.handleInventoryClick(xPos,yPos,clickType)){
		craftingWindow.handleInventoryClick(xPos,yPos,clickType);
	}	

}

bool PlayerState::requestCraft(Recipe* recipeToCraft){
	return playerInventory.craftRecipe(recipeToCraft);	
}
bool PlayerState::addToInventory(Item* itemToAdd){
	return playerInventory.addToInventory(itemToAdd);
}

void PlayerState::toggleInventory(){
	inventoryOpen = !inventoryOpen;
}

void PlayerState::setSoulColor(int color){
	if(color >= 0 && color <= 7){
		soulColor = color;	
	}
}

int PlayerState::getSoulColor(){
	return soulColor;
}

int PlayerState::getSoulVal(){
	return soul;	
}