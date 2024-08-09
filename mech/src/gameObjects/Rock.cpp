
#include "../../headers/gameObjects/Rock.h"
#include "../../headers/TextureManager.h"

Rock::Rock(short id, int xT, int yT, short rockType) : GameObject(2,32,32) {
    ID = id;
    xTile = xT;
    yTile = yT;
    objectTexture = textureManager.gameObjectsTexture; 
    spriteSheetPos = {rockType * 32,0,32,32};
}