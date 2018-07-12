#include "main.hpp"

Engine::Engine(int screenWidth, int screenHeight) : gameStatus(STARTUP), fovRadius(10), screenWidth(screenWidth), screenHeight(screenHeight)
{
  TCODConsole::initRoot(screenWidth, screenHeight, "Cyberpunk Roguelike", false);
  player = new Actor(40, 25, '@', "player", TCODColor::white);
  player->destructible = new PlayerDestructible(30, 2, "your cadaver");
  player->attacker = new Attacker(5);
  player->ai = new PlayerAi();
  actors.push(player);
  map = new Map(80, 45);
}

void Engine::sendToBack(Actor *actor)
{
  actors.remove(actor);
  actors.insertBefore(actor, 0);
}

void Engine::update()
{
  if (gameStatus == STARTUP)
    map->computeFOV();
  gameStatus = IDLE;
  TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &lastKey, NULL);
  player->update();
  if (gameStatus == NEW_TURN)
  {
    for (Actor **iterator = actors.begin(); iterator != actors.end(); iterator++)
    {
      Actor *actor = *iterator;
      if (actor != player)
      {
        actor->update();
      }
    }
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
  player->render();
  TCODConsole::root->print(1, screenHeight - 2, "HP : %d/%d", (int)player->destructible->currentHealth, (int)player->destructible->maxHealth);
}

Engine::~Engine()
{
  actors.clearAndDelete();
  delete map;
}
