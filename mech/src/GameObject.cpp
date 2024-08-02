#include "../headers/GameObject.h"

GameObject::GameObject(short scale, int w, int h){
	objectScale = scale;
	width = scale * w;
	height = scale * h;
	renObj = {0,0,width,height};
}

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