#include "TextureManager.hpp"

SDL_Texture *TextureManager::LoadTexture(const char *filename)
{
    SDL_Surface *surface;
    SDL_Texture *texture;

    if (!(surface = IMG_Load(filename)))
        std::cout << "error creating surface" << std::endl;
    if (!(texture = SDL_CreateTextureFromSurface(Game::renderer, surface)))
        std::cout << "error creating texture: " << SDL_GetError() << std::endl;
	SDL_FreeSurface(surface);
    return (texture);
}

void TextureManager::Draw(SDL_Texture *texture, SDL_Rect srcRect, SDL_Rect dstRect, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, texture, &srcRect, &dstRect, 0.0, NULL, flip);
}
