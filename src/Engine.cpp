#include "main.hpp"

Engine::Engine(int screenWidth, int screenHeight) : gameStatus(STARTUP), fovRadius(10), screenWidth(screenWidth), screenHeight(screenHeight)
{
  TCODConsole::initRoot(screenWidth, screenHeight, "Cyberpunk Roguelike", false);
  player = new Actor(40, 25, '@', "player", TCODColor::white);
  player->destructible = new PlayerDestructible(30, 2, "your cadaver");
  player->attacker = new Attacker(5);
  player->ai = new PlayerAi();
  player->container = new Container(26);
  actors.push(player);
  map = new Map(80, 43);
  gui = new Gui();
  //gui->message(TCODColor::turquoise, "Initializing system...\nSystem started. Enjoy death.");
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
  TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE, &lastKey, &mouse);
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
  gui->render();
}

Engine::~Engine()
{
  actors.clearAndDelete();
  delete map;
  delete gui;
}
