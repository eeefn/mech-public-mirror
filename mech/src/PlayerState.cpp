#include "../headers/PlayerState.h"
PlayerState playerState;

PlayerState::PlayerState(){

}

void PlayerState::toggleInventory(){
	inventoryOpen = !inventoryOpen;
}