#pragma once
#include <SDL.h>
#include "../headers/entities/Entity.h"

class Editor{
    public:
		void setupSelector(Entity* playerEntity);
		void expandSelWindowLeft();
		void expandSelWindowRight();
		void expandSelWindowDown();
		void expandSelWindowUp();
		void moveSelWindowLeft();
		void moveSelWindowRight();
		void moveSelWindowDown();
		void moveSelWindowUp();
		void renderEditorSelection();
		SDL_Rect* getSelWindowRen();
        Editor();
    private:
		SDL_Rect selWindowRen;
};

extern Editor editor;