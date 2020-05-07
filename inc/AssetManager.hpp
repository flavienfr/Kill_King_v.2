#ifndef ASSETMANAGER_HPP
# define ASSETMANAGER_HPP

# include <map>
# include <string>
# include "TextureManager.hpp"
# include "EntityManager.hpp"

class AssetManager
{
private:
	EntityManager *manager;
	std::map<std::string, SDL_Texture *> textures;
public:
	AssetManager(EntityManager *manager);
	~AssetManager();

	void		ClearData();
	void		AddTexture(std::string textureId, const char *filePath);
	SDL_Texture	*GetTexture(std::string textureId);
};

#endif
