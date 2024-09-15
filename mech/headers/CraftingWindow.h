#pragma once
#include <SDL.h>
#include "RenderRects.h"
#include <vector>
#include "./items/ItemCodes.h"

struct Ingredient{
    int itemCode;
    int quantity;
};

struct Recipe{
    Ingredient firstIngredient;
    Ingredient secondIngredient;
    Ingredient result;
};

class CraftingWindow{
    public:
        CraftingWindow(int invPosOnScreenX, int invPosOnScreenY);
        void render();
        void update();
        void scrollUp();
        void scrollDown();
    private:
        void renderVisibleRecipes();
        void renderRecipeOnPanel(Recipe& recipe);
        int scale = 3;
        int minScrollOffset = 0;
        int maxScrollOffset = scale * 53;
        int minYWithinRecipePane = 0;
        int maxYWithinRecipePane = scale * 60;  
        std::vector<Recipe> currentlyCraftableRecipes;
        RenderRect basePanel;
        RenderRect recipePanel;
        RenderRect scrollBar;
        RenderRect selectRecipe;
        SDL_Rect itemPosOnScreen = {0,0,scale*16,scale*16};
};