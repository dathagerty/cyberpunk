#include "libtcod.hpp"
#include "Actor.hpp"
#include "Map.hpp"
#include "Engine.hpp"

Engine::Engine() : fovRadius(10), computeFOV(true)
{
	TCODConsole::initRoot(80, 50, "Cyberpunk Roguelike", false);
	player = new Actor(40, 25, '@', TCODColor::white);
	actors.push(player);
	map = new Map(80, 45);
}

void Engine::update()
{
	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
	switch (key.vk)
	{
	case TCODK_UP:
		if (!map->isWall(player->x, player->y - 1))
		{
			player->y--;
			computeFOV = true;
		}
		break;
	case TCODK_DOWN:
		if (!map->isWall(player->x, player->y + 1))
		{
			player->y++;
			computeFOV = true;
		}
		break;
	case TCODK_LEFT:
		if (!map->isWall(player->x - 1, player->y))
		{
			player->x--;
			computeFOV = true;
		}
		break;
	case TCODK_RIGHT:
		if (!map->isWall(player->x + 1, player->y))
		{
			player->x++;
			computeFOV = true;
		}
		break;
	default:
		break;
	}
	if (computeFOV)
	{
		map->computeFOV();
		computeFOV = false;
	}
}

void Engine::render()
{
	TCODConsole::root->clear();
	map->render();
	for (Actor **iterator = actors.begin(); iterator != actors.end(); iterator++)
	{
		Actor *actor = *iterator;
		if (map->isInFOV(actor->x, actor->y))
		{
			actor->render();
		}
	}
}

Engine::~Engine()
{
	actors.clearAndDelete();
	delete map;
}