#ifndef MAP_HPP
# define MAP_HPP

# include <string>
# include <fstream>
# include "Game.hpp"
# include "TileComponent.hpp"
# include "EntityManager.hpp"

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

	void LoadMap(std::string filePath, int mapSizeX, int mapSizeY);
	void AddTile(int srcRectX, int srcRectY, int x, int y);
};

#endif
