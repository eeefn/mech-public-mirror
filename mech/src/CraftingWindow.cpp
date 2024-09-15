#include "../headers/CraftingWindow.h"
#include "../headers/TextureManager.h"
#include "../headers/WindowManager.h"
#include "../headers/items/ItemFactory.h"

CraftingWindow::CraftingWindow(int invPosOnScreenX, int invPosOnScreenY){
    basePanel.posOnTexture = {0,75,108,75};
    basePanel.posOnScreen = {invPosOnScreenX - (scale * basePanel.posOnTexture.w), invPosOnScreenY, scale*basePanel.posOnTexture.w, scale*basePanel.posOnTexture.h};
    scrollBar.posOnTexture = {198,18,3,7}; 
    scrollBar.posOnScreen = {basePanel.posOnScreen.x + 101*scale, basePanel.posOnScreen.y + 8*scale, scale*scrollBar.posOnTexture.w, scale*scrollBar.posOnTexture.h};
    minScrollOffset += scrollBar.posOnScreen.y;
    maxScrollOffset += scrollBar.posOnScreen.y;
    recipePanel.posOnTexture = {109,75,88,20};
    recipePanel.posOnScreen = {basePanel.posOnScreen.x + 9*scale, basePanel.posOnScreen.y + 9*scale, scale*recipePanel.posOnTexture.w,scale*recipePanel.posOnTexture.h};
    minYWithinRecipePane += basePanel.posOnScreen.y + scale * 6;
    maxYWithinRecipePane += basePanel.posOnScreen.y + scale * 6;
    Recipe testRecipe = {{ItemCodes::STICK,1},{ItemCodes::ROCK,1},{ItemCodes::GARDENBOX,1}};
    currentlyCraftableRecipes.push_back(testRecipe);
}

void CraftingWindow::render(){
    SDL_RenderCopy(windowManager.renderer,textureManager.inventoryTexture,&basePanel.posOnTexture,&basePanel.posOnScreen);
    SDL_RenderCopy(windowManager.renderer,textureManager.inventoryTexture,&scrollBar.posOnTexture,&scrollBar.posOnScreen);    
    renderVisibleRecipes();
}

void CraftingWindow::scrollUp(){
    scrollBar.posOnScreen.y += scale*3;        
    if(scrollBar.posOnScreen.y > maxScrollOffset){
        scrollBar.posOnScreen.y = maxScrollOffset;
    }
}

void CraftingWindow::scrollDown(){
    scrollBar.posOnScreen.y -= scale*3;
    if(scrollBar.posOnScreen.y < minScrollOffset){
        scrollBar.posOnScreen.y = minScrollOffset;
    }
}

void CraftingWindow::update(){
}

void CraftingWindow::renderVisibleRecipes(){
    for(auto recipe : currentlyCraftableRecipes){
        SDL_RenderCopy(windowManager.renderer,textureManager.inventoryTexture,&recipePanel.posOnTexture,&recipePanel.posOnScreen);
        renderRecipeOnPanel(recipe);
    }
}

void CraftingWindow::renderRecipeOnPanel(Recipe& recipe){
    Item* mockItem = itemFactory.makeItem(recipe.firstIngredient.itemCode,recipe.firstIngredient.quantity);
    itemPosOnScreen.x = recipePanel.posOnScreen.x + (2 * scale); 
    itemPosOnScreen.y = recipePanel.posOnScreen.y + (2 * scale); 
    SDL_RenderCopy(windowManager.renderer,textureManager.itemsTexture,mockItem->getSpriteSheetPos(),&itemPosOnScreen);
    delete mockItem;
    mockItem = itemFactory.makeItem(recipe.secondIngredient.itemCode,recipe.secondIngredient.quantity);
    itemPosOnScreen.x = recipePanel.posOnScreen.x + ((2 + 32 + 1) * scale); 
    itemPosOnScreen.y = recipePanel.posOnScreen.y + (2 * scale); 
    SDL_RenderCopy(windowManager.renderer,textureManager.itemsTexture,mockItem->getSpriteSheetPos(),&itemPosOnScreen);
    delete mockItem;
    mockItem = itemFactory.makeItem(recipe.result.itemCode,recipe.result.quantity);
    itemPosOnScreen.x = recipePanel.posOnScreen.x + ((2 + 64 + 3) * scale); 
    itemPosOnScreen.y = recipePanel.posOnScreen.y + (2 * scale); 
    SDL_RenderCopy(windowManager.renderer,textureManager.itemsTexture,mockItem->getSpriteSheetPos(),&itemPosOnScreen);
}