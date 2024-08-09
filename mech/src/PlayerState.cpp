#include "../headers/PlayerState.h"
PlayerState playerState;

PlayerState::PlayerState(){

}

void PlayerState::toggleInventory(){
	inventoryOpen = !inventoryOpen;
}

void PlayerState::setSoulColor(int color){
	if(color >= 0 && color <= 7){
		soulColor = color;	
	}
}

bool PlayerState::addToInventory(Item* itemToAdd){
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