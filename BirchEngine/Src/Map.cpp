#include "Map.h"
#include <fstream>
#include "Game.h"

Map::Map()
{
	
}

Map::~Map()
{
	
}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			if(!mapFile.eof())
			{
				mapFile.get(tile);
				switch (tile)
				{

				case '0' :
					Game::AddTile(0, j * 32, i * 32);
					break;
				case '1':
					Game::AddTile(1, j * 32, i * 32);
					break;
				case '2':
					Game::AddTile(2, j * 32, i * 32);
					break;
				default:
					break;
				}
				
				mapFile.ignore();
			}
		}
	}
}