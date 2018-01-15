#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS\ECS.h"
#include "ECS\Components.h"
extern Manager manager;

Map::Map(const char* mf, int ms, int ts = 32) : mapFile(mf), mapScale(ms)
{
	tileSize = ts;
}

Map::~Map()
{
}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	int scaleSize = tileSize * mapScale;
	char c;
	std::fstream mapfile;
	mapfile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapfile.get(c);
			srcY = atoi(&c) * tileSize;
			mapfile.get(c);
			srcX = atoi(&c) * tileSize;
			AddTile(srcX, srcY, x * scaleSize, y * scaleSize);
			mapfile.ignore();
		}
	}

	mapfile.ignore();

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapfile.get(c);
			if (c == '1')
			{
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * scaleSize, y * scaleSize, scaleSize);
				tcol.addGroup(Game::groupColliders);
			}
			mapfile.ignore();
		}
	}

	mapfile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, mapFile);
	tile.addGroup(Game::groupMap);
}