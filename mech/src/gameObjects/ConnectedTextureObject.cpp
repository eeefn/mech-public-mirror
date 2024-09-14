#include "../../headers/gameObjects/ConnectedTextureObject.h"
#include "../../headers/gameObjects/GameObjectManager.h"

ConnectedTextureObject::ConnectedTextureObject(int xPosUnconnectedTex, int yPosUnconnectedTex){
    originalPosOnTexture = {xPosUnconnectedTex,yPosUnconnectedTex,scaledWidth/objectScale,scaledHeight/objectScale};    
}
void ConnectedTextureObject::updateRenderTextureL(){
    hasRightNeighbor = true;
    hasLeftNeighbor = gameObjectManager.checkForLeftNeighbor(this);
    handleTextureBasedOnNeighbors();
}

void ConnectedTextureObject::updateRenderTextureR(){
    hasLeftNeighbor = true;
    hasRightNeighbor = gameObjectManager.checkForRightNeighbor(this);
    handleTextureBasedOnNeighbors();
}

void ConnectedTextureObject::handleTextureBasedOnNeighbors(){
    renderRects.posOnTexture = originalPosOnTexture;
    if(hasLeftNeighbor && hasRightNeighbor){
        renderRects.posOnTexture.x = 2 * originalPosOnTexture.w;
    }
    else if(hasLeftNeighbor){
        renderRects.posOnTexture.x = 3 * originalPosOnTexture.w;
    }
    else if(hasRightNeighbor){
        renderRects.posOnTexture.x = 1 * originalPosOnTexture.w;
    }
    else{
    }
}

bool ConnectedTextureObject::place(){
    hasLeftNeighbor = gameObjectManager.checkForLeftNeighbor(this);
    hasRightNeighbor = gameObjectManager.checkForRightNeighbor(this);
    handleTextureBasedOnNeighbors();
    return true;
}