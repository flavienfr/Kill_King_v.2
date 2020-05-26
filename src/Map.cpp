#include "Map.hpp"

Map::Map(std::string textureId, int scale, int tileSize) :
textureId(textureId), scale(scale), tileSize(tileSize)
{
}

Map::~Map()
{
}

void Map::LoadMap(std::string folderPath, int AssetSizeX, int nbLayer)
{
	std::fstream	mapFile;
	std::string		line;

	for (int layer = 0; layer < nbLayer; layer++)
	{
		mapFile.open(folderPath + std::to_string(layer) + ".csv");
		if (!mapFile.is_open())
			std::cerr << "File map " << folderPath + std::to_string(layer) + "csv" << " not open" << std::endl;
		int	y = 0;
		while (getline(mapFile, line))
		{
			std::stringstream	ss(line);
			std::string			value;
			int	x = 0;
			while (getline(ss, value, ','))
			{
				if (stoi(value) != -1)
				{
					int srcRecY = (stoi(value) / AssetSizeX) * tileSize;
					int srcRecX = (stoi(value) % AssetSizeX) * tileSize;
					AddTile(srcRecX, srcRecY, x * (tileSize * scale), y * (tileSize * scale), static_cast<LayerType>(layer));
				}
				x++;
			}
			y++;
		}
		mapFile.close();
	}
}

void Map::AddTile(int srcRectX, int srcRectY, int x, int y, LayerType layer)
{
	Entity &newTile = manager.AddEntity("Tile", layer);

	newTile.AddComponent<TileComponent>(srcRectX, srcRectY, x, y, tileSize, scale, textureId);
}
