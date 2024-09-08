#include "../headers/PlayerState.h"

PlayerState playerState;

PlayerState::PlayerState(){

}

void PlayerState::update(){
	hotbar.update();
}
void PlayerState::handleInventoryClick(int xPos, int yPos,Uint32 clickType){
	playerInventory.handleInventoryClick(xPos,yPos,clickType);	
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