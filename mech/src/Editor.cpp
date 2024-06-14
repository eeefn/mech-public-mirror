#include "../headers/Editor.h"
#include "../headers/constants.h"
#include "../headers/WindowManager.h"

Editor editor;

Editor::Editor(){
    return;
}

void Editor::expandSelWindowLeft(){
	selWindowRen.w -= TILE_DIM;
	if (selWindowRen.w < TILE_DIM) {
		selWindowRen.w = TILE_DIM;
	}
}

void Editor::expandSelWindowRight(){
	selWindowRen.w += TILE_DIM;
}

void Editor::expandSelWindowDown(){
	selWindowRen.h += TILE_DIM;
}

void Editor::moveSelWindowRight(){
	selWindowRen.x += TILE_DIM;
}

void Editor::moveSelWindowLeft(){
	selWindowRen.x -= TILE_DIM;
	if (selWindowRen.x <= 0) {
		selWindowRen.x = 0;
	}

}

void Editor::expandSelWindowUp(){
	selWindowRen.h -= TILE_DIM;
	if (selWindowRen.h < TILE_DIM) {
		selWindowRen.h = TILE_DIM;
	}
}

void Editor::moveSelWindowDown(){
	selWindowRen.y += TILE_DIM;
}

void Editor::moveSelWindowUp(){
	selWindowRen.y -= TILE_DIM;
	if (selWindowRen.y <= 0) {
		selWindowRen.y = 0;
	}
}

SDL_Rect* Editor::getSelWindowRen(){
	return &selWindowRen;
}

void Editor::setupSelector(Entity* playerEntity){
	selWindowRen.h = TILE_DIM;
	selWindowRen.w = TILE_DIM;
	selWindowRen.x = (playerEntity->displayRect.x % TILE_DIM);
	selWindowRen.y = /*selOffY - */(playerEntity->displayRect.y % TILE_DIM);

}
void Editor::renderEditorSelection(){
	SDL_SetRenderDrawColor(windowManager.renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(windowManager.renderer, &editor.selWindowRen);
}
