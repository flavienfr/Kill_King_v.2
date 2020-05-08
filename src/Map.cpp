#include "Map.hpp"

Map::Map(std::string textureId, int scale, int tileSize) :
textureId(textureId), scale(scale), tileSize(tileSize)
{
}

Map::~Map()
{
}

void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY)
{// change this funtcion for a bigger tile map
	std::fstream mapFile;

	mapFile.open(filePath);
	for (int y = 0; y < mapSizeY ; y++)
	{
		for (int x = 0; x < mapSizeX ; x++)
		{
			char c;
			mapFile.get(c);
			int srcRecY = atoi(&c) * tileSize;
			mapFile.get(c);
			int srcRecX = atoi(&c) * tileSize;
			AddTile(srcRecX, srcRecY, x * (tileSize * scale), y * (tileSize * scale));
			mapFile.ignore();
		}
	}
	mapFile.close();
}

void Map::AddTile(int srcRectX, int srcRectY, int x, int y)
{
	Entity &newTile = manager.AddEntity("Tile");

	newTile.AddComponent<TileComponent>(srcRectX, srcRectY, x, y, tileSize, scale, textureId);
}
