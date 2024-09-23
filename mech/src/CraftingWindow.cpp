#include "../headers/CraftingWindow.h"
#include "../headers/TextureManager.h"
#include "../headers/WindowManager.h"
#include "../headers/items/ItemFactory.h"
#include "../headers/Collider.h"
#include "../headers/PlayerState.h"
#include <stdlib.h>
#include <stdexcept>

CraftingWindow::CraftingWindow(int invPosOnScreenX, int invPosOnScreenY){
    basePanel.posOnTexture = {0,75,108,75};
    basePanel.posOnScreen = {invPosOnScreenX - (scale * basePanel.posOnTexture.w), invPosOnScreenY, scale*basePanel.posOnTexture.w, scale*basePanel.posOnTexture.h};
    scrollBar.posOnTexture = {198,18,3,7}; 
    scrollBar.posOnScreen = {basePanel.posOnScreen.x + 101*scale, basePanel.posOnScreen.y + 8*scale, scale*scrollBar.posOnTexture.w, scale*scrollBar.posOnTexture.h};
    minScrollBarOffset += scrollBar.posOnScreen.y;
    maxScrollBarOffset += scrollBar.posOnScreen.y;
    recipePanel.posOnTexture = {109,75,88,20};
    recipePanel.posOnScreen = {basePanel.posOnScreen.x + 9*scale, basePanel.posOnScreen.y + 9*scale, scale*recipePanel.posOnTexture.w,scale*recipePanel.posOnTexture.h};
    minYWithinRecipePane += basePanel.posOnScreen.y + scale * 8;
    maxYWithinRecipePane += basePanel.posOnScreen.y + scale * 8;
    Recipe* testRecipe = new Recipe({{ItemCodes::STICK,1},{ItemCodes::ROCK,1},{ItemCodes::GARDENBOX,1}});
    Recipe* testRecipe1 = new Recipe({{ItemCodes::YUCCALEAF,1},{ItemCodes::YUCCALEAF,1},{ItemCodes::GARDENBOX,1}});
    Recipe* testRecipe2 = new Recipe({{ItemCodes::STICK,1},{ItemCodes::ROCK,1},{ItemCodes::GARDENBOX,1}});
    currentlyCraftableRecipes.push_back(testRecipe);
    currentlyCraftableRecipes.push_back(testRecipe1);
    currentlyCraftableRecipes.push_back(testRecipe2);
}

void CraftingWindow::render(){
    SDL_RenderCopy(windowManager.renderer,textureManager.inventoryTexture,&basePanel.posOnTexture,&basePanel.posOnScreen);
    SDL_RenderCopy(windowManager.renderer,textureManager.inventoryTexture,&scrollBar.posOnTexture,&scrollBar.posOnScreen);    
    renderVisibleRecipes();
}

void CraftingWindow::scrollDown(){
    scrollBar.posOnScreen.y += scale*3;
    if(scrollBar.posOnScreen.y > maxScrollBarOffset){
        scrollBar.posOnScreen.y = maxScrollBarOffset;
    }
    paneOffset -= scale*3; 
}

void CraftingWindow::scrollUp(){
    scrollBar.posOnScreen.y -= scale*3;
    if(scrollBar.posOnScreen.y < minScrollBarOffset){
        scrollBar.posOnScreen.y = minScrollBarOffset;
    }
    paneOffset += scale*3;
}

void CraftingWindow::update(){
}

void CraftingWindow::renderVisibleRecipes(){
    for(unsigned int i = 0; i < currentlyCraftableRecipes.size(); i++){
        Recipe* currentRecipe = currentlyCraftableRecipes.at(i);
        recipePanel.posOnScreen.y += paneOffset + (recipePanel.posOnScreen.h * i);
        renderElementWithinPane(*textureManager.inventoryTexture,recipePanel);
        renderRecipeOnPanel(currentRecipe);
        recipePanel.posOnScreen.y -= paneOffset + (recipePanel.posOnScreen.h * i);
    }
}

void CraftingWindow::renderRecipeOnPanel(Recipe* recipe){
    renderIngredientOnPanel(recipe->firstIngredient, 2 * scale);
    renderIngredientOnPanel(recipe->secondIngredient,35 * scale);
    renderIngredientOnPanel(recipe->result, 69 * scale);
}

int CraftingWindow::calcChopVal(SDL_Rect& posOnScreen){
    int chopVal = 0;
    if(posOnScreen.y <= minYWithinRecipePane){
        chopVal = (posOnScreen.y - minYWithinRecipePane) / 3;
    }
    else if(posOnScreen.y + posOnScreen.h >= maxYWithinRecipePane){
        chopVal = (posOnScreen.y + posOnScreen.h - maxYWithinRecipePane) / 3;
    }
    return chopVal;
}

void CraftingWindow::renderIngredientOnPanel(Ingredient& ingredient, int xOffset){
    Item* mockItem = itemFactory.makeItem(ingredient.itemCode,ingredient.quantity);
    itemPosOnScreen.x = recipePanel.posOnScreen.x + xOffset; 
    itemPosOnScreen.y = recipePanel.posOnScreen.y + (2 * scale); 
    SDL_Rect posOnTexture = *mockItem->getSpriteSheetPos();
    RenderRect renRect = {posOnTexture,itemPosOnScreen};
    renderElementWithinPane(*textureManager.itemsTexture,renRect);
    delete mockItem;
}

void CraftingWindow::renderElementWithinPane(SDL_Texture& tex,RenderRect rect){
    int chopVal = calcChopVal(rect.posOnScreen);
    if(abs(chopVal) <= rect.posOnTexture.h){
        if(chopVal == 0){
            SDL_RenderCopy(windowManager.renderer,&tex,&rect.posOnTexture,&rect.posOnScreen);
        }
        else if(chopVal < 0){
            chopVal = chopVal * -1;
            rect.posOnTexture.y += chopVal;
            rect.posOnTexture.h -= chopVal;
            rect.posOnScreen.y += chopVal * scale;
            rect.posOnScreen.h -= chopVal * scale;
            SDL_RenderCopy(windowManager.renderer,&tex,&rect.posOnTexture,&rect.posOnScreen);
        }
        else{
            rect.posOnTexture.h -= chopVal;
            rect.posOnScreen.h -= chopVal * scale;
            SDL_RenderCopy(windowManager.renderer,&tex,&rect.posOnTexture,&rect.posOnScreen);
        }
    }
}
void CraftingWindow::handleInventoryClick(int xPos,int yPos, Uint32 clickType){
    SDL_Rect recipePane = {basePanel.posOnScreen.x + 9*scale, basePanel.posOnScreen.y + 9*scale,90*scale,60*scale};
    if(collider.checkPointWithinRect(xPos,yPos,recipePane)){
        Recipe* recipe = getRecipeAtClick(xPos, yPos);
        if(recipe != nullptr){
           playerState.requestCraft(recipe);
        }
    }
}

Recipe* CraftingWindow::getRecipeAtClick(int xPos, int yPos){
    int yPosRelativeToCraftingBox = yPos - (basePanel.posOnScreen.y + 9*scale) - paneOffset;
    int indexOfRecipe = yPosRelativeToCraftingBox / recipePanel.posOnScreen.h;
    try{
        Recipe* returnRecipe = currentlyCraftableRecipes.at(indexOfRecipe);        
        return returnRecipe;
    }
    catch(std::exception e){
        return nullptr;
    }

}