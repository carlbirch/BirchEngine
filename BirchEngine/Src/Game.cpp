#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include <string>
#include "AssetManager.h"

Manager manager;
Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
AssetManager* Game::assets = new AssetManager(&manager);

SDL_Rect Game::cameraOffset = { 0, 0, 800, 640 };

bool Game::isRunning = false;

auto& player(manager.addEntity());

Game::Game()
{
}

Game::~Game()
{
	delete assets;
}

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
	

	//add textures to master list

	assets->AddTexture("terrain_tiles", "assets/terrain_ss.png");
	assets->AddTexture("projectile", "assets/proj_tex.png");
	assets->AddTexture("player_anims", "assets/player_anims.png");
	

	// terrain sprite sheet, mapscale, tilesize
	map = new Map("terrain_tiles", 3, 32);

	//ecs implementation

	map->LoadMap("assets/map.map", 25, 20);

	player.addComponent<TransformComponent>(800.0f, 740.0f, 32, 32, 4);
	player.addComponent<SpriteComponent>("player_anims", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	Vector2D pos = player.getComponent<TransformComponent>().position;
	int speed = 2;
	assets->CreateProjectile(pos, speed, "projectile");

}
auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

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

	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	manager.refresh();
	manager.update();

	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(playerCol, cCol))
		{
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	for (auto& p : projectiles)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			std::cout << "player hit!" << std::endl;
			p->destroy();
		}
	}
	
	cameraOffset.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - 400);
	cameraOffset.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - 320);

	if (cameraOffset.x < 0)
		cameraOffset.x = 0;
	if (cameraOffset.y < 0)
		cameraOffset.y = 0;
	if (cameraOffset.x > cameraOffset.w)
		cameraOffset.x = cameraOffset.w;
	if (cameraOffset.y > cameraOffset.h)
		cameraOffset.y = cameraOffset.h;
}

void Game::render()
{
	SDL_RenderClear(renderer);

	for (auto& t : tiles)
	{
		t->draw();
	}
	
	for (auto& c : colliders)
	{
		c->draw();
	}


	for (auto& p : players)
	{
		p->draw();
	}

	for (auto& p : projectiles)
	{
		p->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}