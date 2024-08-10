#include "../headers/PlayerState.h"

PlayerState playerState;

PlayerState::PlayerState(){

}

void PlayerState::handleInventoryClick(int xPos, int yPos,Uint32 clickType){
	playerInventory.handleInventoryClick(xPos,yPos,clickType);	
}

void PlayerState::addToInventory(Item* itemToAdd){
	playerInventory.addToInventory(itemToAdd);
}

void PlayerState::toggleInventory(){
	inventoryOpen = !inventoryOpen;
}

void PlayerState::setSoulColor(int color){
	if(color >= 0 && color <= 7){
		soulColor = color;	
	}
}