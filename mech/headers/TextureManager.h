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
        SDL_Texture* rocksTexture;
        void initPermanentTextures(SDL_Renderer* renderer);
        void initializeTexture(SDL_Texture** textureToInit, const char* filePath, SDL_Renderer* renderer);
};

extern TextureManager textureManager;