#include "FontManager.hpp"

TTF_Font *FontManager::LoadFont(const char *fileName, int fontSize)
{
	TTF_Font *font = TTF_OpenFont(fileName, fontSize);
	if(!font)
		std::cerr << "TTF_OpenFont: " << TTF_GetError() <<std::endl;
	return (font);
}

void FontManager::Draw(SDL_Texture *texture, SDL_Rect position)
{
	SDL_RenderCopy(Game::renderer, texture, NULL, &position);
}
