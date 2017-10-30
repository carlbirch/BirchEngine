#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;

Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

std::vector<ColliderComponent*> Game::colliders;

enum eGroups : std::size_t
{
	gTiles,
	gPlayer,
	gEnemies
};

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	map = new Map();

	//ecs implementation

	Map::LoadMap("assets/p16x16.map", 12, 12);

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("assets/player_idle.png", 4, 100);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.AddGroup(gPlayer);

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/dirt.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.AddGroup(gTiles);
	
}

void Game::handleEvents()
{
	
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}


void Game::update()
{
	manager.refresh();
	manager.update();
	for (auto i : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *i);
	}
	
}

auto& tiles(manager.getGroup(gTiles));
auto& players(manager.getGroup(gPlayer));
auto& enemies(manager.getGroup(gEnemies));

void Game::render()
{
	SDL_RenderClear(renderer);

	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& e : enemies)
	{
		e->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::AddTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
	tile.addComponent<ColliderComponent>("tile");
	tile.AddGroup(gTiles);
}
