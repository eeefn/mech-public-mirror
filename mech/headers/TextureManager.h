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
        void initPermanentTextures(SDL_Renderer* renderer);
};

extern TextureManager textureManager;