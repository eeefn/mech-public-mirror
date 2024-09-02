#include <SDL.h>
#include <string>

class TextureManager{
    public:
        SDL_Texture* tileTexture;
        SDL_Texture* gameObjectTexture;
        SDL_Texture* guiTexture;
        SDL_Texture* mechTexture;
        SDL_Texture* mechAtTexture;
        SDL_Texture* spriteTexture;
        SDL_Texture* headTexture;
        SDL_Texture* torsoTexture;
        SDL_Texture* legsTexture;
        SDL_Texture* mushFullTexture;
        SDL_Texture* caveBackroundTexture;
        SDL_Texture* portalTexture;
        SDL_Texture* gameObjectsTexture;
        SDL_Texture* inventoryTexture;
        SDL_Texture* itemsTexture;
        SDL_Texture* numberTexture;
        SDL_Texture* soulSwordSwing;
        void initPermanentTextures(SDL_Renderer* renderer);
        void initializeTexture(SDL_Texture** textureToInit, const char* filePath, SDL_Renderer* renderer);
};

extern TextureManager textureManager;