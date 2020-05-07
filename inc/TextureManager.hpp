#ifndef TEXTUREMANAGER_HPP
# define TEXTUREMANAGER_HPP

# include "Game.hpp"

class TextureManager
{
public:
	static SDL_Texture *LoadTexture(const char *filename);
	static void Draw(SDL_Texture *texture, SDL_Rect srcRect, SDL_Rect dstRect, SDL_RendererFlip flip);
};

#endif
