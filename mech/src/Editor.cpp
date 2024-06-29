#include "../headers/Editor.h"
#include "../headers/constants.h"
#include "../headers/WindowManager.h"

Editor editor;

Editor::Editor(){
    return;
}

void Editor::expandSelWindowLeft(){
	selWindowRen.w -= mapInfo.TILE_DIM;
	if (selWindowRen.w < mapInfo.TILE_DIM) {
		selWindowRen.w = mapInfo.TILE_DIM;
	}
}

void Editor::expandSelWindowRight(){
	selWindowRen.w += mapInfo.TILE_DIM;
}

void Editor::expandSelWindowDown(){
	selWindowRen.h += mapInfo.TILE_DIM;
}

void Editor::moveSelWindowRight(){
	selWindowRen.x += mapInfo.TILE_DIM;
}

void Editor::moveSelWindowLeft(){
	selWindowRen.x -= mapInfo.TILE_DIM;
	if (selWindowRen.x <= 0) {
		selWindowRen.x = 0;
	}

}

void Editor::expandSelWindowUp(){
	selWindowRen.h -= mapInfo.TILE_DIM;
	if (selWindowRen.h < mapInfo.TILE_DIM) {
		selWindowRen.h = mapInfo.TILE_DIM;
	}
}

void Editor::moveSelWindowDown(){
	selWindowRen.y += mapInfo.TILE_DIM;
}

void Editor::moveSelWindowUp(){
	selWindowRen.y -= mapInfo.TILE_DIM;
	if (selWindowRen.y <= 0) {
		selWindowRen.y = 0;
	}
}

SDL_Rect* Editor::getSelWindowRen(){
	return &selWindowRen;
}

void Editor::setupSelector(Entity* playerEntity){
	selWindowRen.h = mapInfo.TILE_DIM;
	selWindowRen.w = mapInfo.TILE_DIM;
	selWindowRen.x = (playerEntity->displayRect.x % mapInfo.TILE_DIM);
	selWindowRen.y = /*selOffY - */(playerEntity->displayRect.y % mapInfo.TILE_DIM);

}
void Editor::renderEditorSelection(){
	SDL_SetRenderDrawColor(windowManager.renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(windowManager.renderer, &editor.selWindowRen);
}
