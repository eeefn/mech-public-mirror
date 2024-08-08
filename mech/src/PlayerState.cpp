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