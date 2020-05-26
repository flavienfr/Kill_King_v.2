#ifndef MAP_HPP
# define MAP_HPP

# include <fstream>
# include <string>
# include "Game.hpp"
# include "Map.hpp"
# include "EntityManager.hpp"
# include "TileComponent.hpp"

extern EntityManager manager;

class Map
{
private:
	std::string	textureId;
	int			scale;
	int			tileSize;

public:
	Map(std::string textureId, int scale, int tileSize);
	~Map();

	void LoadMap(std::string filePath, int AssetSizeX, int nbLayer);
	void AddTile(int srcRectX, int srcRectY, int x, int y, LayerType layer);
};

#endif
