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
        void handleInventoryClick(int xPos,int yPos, Uint32 clickType);
    private:
        void renderVisibleRecipes();
        void renderRecipeOnPanel(Recipe* recipe);
        void renderIngredientOnPanel(Ingredient& ingredient, int xOffset);
        void renderElementWithinPane(SDL_Texture& tex,RenderRect rect);
        Recipe* getRecipeAtClick(int xPos, int yPos);
        int calcChopVal(SDL_Rect& posOnScreen);
        int scale = 3;
        int minScrollBarOffset = 0;
        int maxScrollBarOffset = scale * 53;
        int minRecipePaneOffset = 0;
        int maxRecipePaneOffset = 0;
        int paneOffset = 0;
        int minYWithinRecipePane = 0;
        int maxYWithinRecipePane = scale * 60;  
        std::vector<Recipe*> currentlyCraftableRecipes;
        RenderRect basePanel;
        RenderRect recipePanel;
        RenderRect scrollBar;
        RenderRect selectRecipe;
        SDL_Rect itemPosOnScreen = {0,0,scale*16,scale*16};
};