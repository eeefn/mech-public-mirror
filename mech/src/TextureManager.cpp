#include "../headers/TextureManager.h"


TextureManager textureManager;

void TextureManager::initPermanentTextures(SDL_Renderer* renderer){
	SDL_Surface* tileMapSurface = SDL_LoadBMP("../resources/tile4.bmp");
	if (!tileMapSurface) { fprintf(stderr, "could not find tile images"); }
	tileTexture = SDL_CreateTextureFromSurface(renderer, tileMapSurface);
	SDL_FreeSurface(tileMapSurface);
    
	SDL_Surface* gameObjectSurface = SDL_LoadBMP("../resources/objSheetv1.bmp");
	if (!gameObjectSurface) { fprintf(stderr, "could not find gameObject texture"); return; }
	gameObjectTexture = SDL_CreateTextureFromSurface(renderer, gameObjectSurface);
    SDL_FreeSurface(gameObjectSurface);

	SDL_Surface* guiSurface = SDL_LoadBMP("../resources/gui.bmp");
	if (!guiSurface) { fprintf(stderr, "could not find gui image"); return; }
	guiTexture = SDL_CreateTextureFromSurface(renderer, guiSurface);
    SDL_FreeSurface(guiSurface);

	SDL_Surface* mechSurface = SDL_LoadBMP("../resources/mech.bmp");
	if (!mechSurface) { fprintf(stderr, "could not find mech image"); return; }
	mechTexture = SDL_CreateTextureFromSurface(renderer, mechSurface);
    SDL_FreeSurface(mechSurface);

	SDL_Surface* mechAtSurface = SDL_LoadBMP("../resources/handAt.bmp");
	if (!mechAtSurface) { fprintf(stderr, "could not find hands"); return; }
	mechAtTexture = SDL_CreateTextureFromSurface(renderer, mechAtSurface);
    SDL_FreeSurface(mechAtSurface);

	SDL_Surface* spriteSheetSurface = SDL_LoadBMP("../resources/mushBoyJ.bmp");
	if (!spriteSheetSurface) { fprintf(stderr, "could not find spritesheet"); return; }
	spriteTexture = SDL_CreateTextureFromSurface(renderer, spriteSheetSurface);
	SDL_FreeSurface(spriteSheetSurface);

	SDL_Surface* headSurface = SDL_LoadBMP("../resources/headIsolated.bmp");
	if (!headSurface) { fprintf(stderr, "could not find playerHead"); return; }
	headTexture = SDL_CreateTextureFromSurface(renderer, headSurface);
	SDL_FreeSurface(headSurface);

	SDL_Surface* torsoSurface = SDL_LoadBMP("../resources/torsoIsolated.bmp");
	if (!torsoSurface) { fprintf(stderr, "could not find playerTorso"); return; }
	torsoTexture = SDL_CreateTextureFromSurface(renderer, torsoSurface);
	SDL_FreeSurface(torsoSurface);

	SDL_Surface* legsSurface = SDL_LoadBMP("../resources/legsIsolated.bmp");
	if (!legsSurface) { fprintf(stderr, "could not find playerLegs"); return; }
	legsTexture = SDL_CreateTextureFromSurface(renderer, legsSurface);
	SDL_FreeSurface(legsSurface);

	SDL_Surface* mushGrowSurface = SDL_LoadBMP("../resources/mushroomGrow.bmp");
	if (!mushGrowSurface) { fprintf(stderr, "could not find mushGrow"); return; }
	mushGrowTexture = SDL_CreateTextureFromSurface(renderer, mushGrowSurface);
	SDL_FreeSurface(mushGrowSurface);
}