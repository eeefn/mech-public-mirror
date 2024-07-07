#include "../headers/GameObject.h"
#include <vector>


bool GameObject::place() {
	return false;
}

bool GameObject::destroy() {
	return false;
}

bool GameObject::activate() {
	return false;
}

bool GameObject::deactivate(){
	return false;
}

void GameObject::highlight(bool highlight){
	highlighted = highlight;
}