#include "../headers/CraftingWindow.h"
#include "../headers/TextureManager.h"
#include "../headers/WindowManager.h"

CraftingWindow::CraftingWindow(int invPosOnScreenX, int invPosOnScreenY){
    basePanel.posOnTexture = {0,75,110,75};
    basePanel.posOnScreen = {invPosOnScreenX - (scale * basePanel.posOnTexture.w), invPosOnScreenY, scale*basePanel.posOnTexture.w, scale*basePanel.posOnTexture.h};
    scrollBar.posOnTexture = {198,18,3,7}; 
    scrollBar.posOnScreen = {basePanel.posOnScreen.x + 103*scale, basePanel.posOnScreen.y + 8*scale, scale*scrollBar.posOnTexture.w, 3*scrollBar.posOnTexture.h};
    minScrollOffset += scrollBar.posOnScreen.y;
    maxScrollOffset += scrollBar.posOnScreen.y;
}

void CraftingWindow::render(){
    SDL_RenderCopy(windowManager.renderer,textureManager.inventoryTexture,&basePanel.posOnTexture,&basePanel.posOnScreen);
    SDL_RenderCopy(windowManager.renderer,textureManager.inventoryTexture,&scrollBar.posOnTexture,&scrollBar.posOnScreen);    
    for(auto recipe : currentlyCraftableRecipes){
        //getRecipePosition(index,scrollOffset);
    }
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