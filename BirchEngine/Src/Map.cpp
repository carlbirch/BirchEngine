#include "Map.h"
#include <fstream>
#include "Game.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::LoadMap(std::string path, int xSize, int ySize)
{
	char tile;
	std::fstream mapFile;

	mapFile.open(path);

	for (int y = 0; y < ySize; y++)
	{
		for (int x = 0; x < xSize; x++)
		{
			mapFile.get(tile);
			Game::AddTile(atoi(&tile), x * 32, y * 32);
			mapFile.ignore();
		}
	}

	mapFile.close();
}
