#include "../headers/TextureManager.h"


TextureManager textureManager;

void TextureManager::initPermanentTextures(SDL_Renderer* renderer){
	SDL_Surface* tileMapSurface = SDL_LoadBMP("./resources/tile4.bmp");
	if (!tileMapSurface) { fprintf(stderr, "could not find tile images"); }
	tileTexture = SDL_CreateTextureFromSurface(renderer, tileMapSurface);
	SDL_FreeSurface(tileMapSurface);
    
	SDL_Surface* gameObjectSurface = SDL_LoadBMP("./resources/objSheetv1.bmp");
	if (!gameObjectSurface) { fprintf(stderr, "could not find gameObject texture"); return; }
	gameObjectTexture = SDL_CreateTextureFromSurface(renderer, gameObjectSurface);
    SDL_FreeSurface(gameObjectSurface);

	SDL_Surface* guiSurface = SDL_LoadBMP("./resources/gui.bmp");
	if (!guiSurface) { fprintf(stderr, "could not find gui image"); return; }
	guiTexture = SDL_CreateTextureFromSurface(renderer, guiSurface);
    SDL_FreeSurface(guiSurface);

	SDL_Surface* mechSurface = SDL_LoadBMP("./resources/mech.bmp");
	if (!mechSurface) { fprintf(stderr, "could not find mech image"); return; }
	mechTexture = SDL_CreateTextureFromSurface(renderer, mechSurface);
    SDL_FreeSurface(mechSurface);

	SDL_Surface* mechAtSurface = SDL_LoadBMP("./resources/handAt.bmp");
	if (!mechAtSurface) { fprintf(stderr, "could not find hands"); return; }
	mechAtTexture = SDL_CreateTextureFromSurface(renderer, mechAtSurface);
    SDL_FreeSurface(mechAtSurface);

	SDL_Surface* spriteSheetSurface = SDL_LoadBMP("./resources/mushBoyJ.bmp");
	if (!spriteSheetSurface) { fprintf(stderr, "could not find spritesheet"); return; }
	spriteTexture = SDL_CreateTextureFromSurface(renderer, spriteSheetSurface);
	SDL_FreeSurface(spriteSheetSurface);
}