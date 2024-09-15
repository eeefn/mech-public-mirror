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
};

class CraftingWindow{
    public:
        CraftingWindow(int invPosOnScreenX, int invPosOnScreenY);
        void render();
        void update();
        void scrollUp();
        void scrollDown();
    private:
        int scale = 3;
        int minScrollOffset = 0;
        int maxScrollOffset = 3 * 53;
        std::vector<Recipe> currentlyCraftableRecipes;
        RenderRect basePanel;
        RenderRect recipePanel;
        RenderRect scrollBar;
        RenderRect selectRecipe;
};