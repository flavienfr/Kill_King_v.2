#include "AssetManager.hpp"

AssetManager::AssetManager(EntityManager *manager) : manager(manager)
{
}

AssetManager::~AssetManager()
{
	ClearData();
}

void AssetManager::ClearData()
{
	//std::cout << "AssetManager ClearData"<< std::endl;
	for (auto &texture: textures)//do we need to do that
		SDL_DestroyTexture(texture.second);
	for (auto &font: fonts)//do we need to do that
		TTF_CloseFont(font.second);
	textures.clear();
	fonts.clear();
}

void AssetManager::AddTexture(std::string textureId, const char *filePath)
{
	textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}

void AssetManager::AddFont(std::string fontId, const char *filePath, int fontSize)
{
	fonts.emplace(fontId, FontManager::LoadFont(filePath, fontSize));
}

SDL_Texture *AssetManager::GetTexture(std::string textureId)
{
	return (textures[textureId]);
}

TTF_Font	*AssetManager::GetFont(std::string fontId)
{
	return (fonts[fontId]);
}
