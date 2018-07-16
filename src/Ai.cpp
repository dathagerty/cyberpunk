#include <math.h>
#include "main.hpp"

static const int TRACKING_TURNS = 3;

void PlayerAi::update(Actor *owner)
{
  if (owner->destructible->isDead())
  {
    return;
  }

  int dx = 0, dy = 0;
  switch (engine.lastKey.vk)
  {
  case TCODK_UP:
    dy = -1;
    break;
  case TCODK_DOWN:
    dy = 1;
    break;
  case TCODK_LEFT:
    dx = -1;
    break;
  case TCODK_RIGHT:
    dx = 1;
    break;
  case TCODK_CHAR:
    handleActionKey(owner, engine.lastKey.c);
    break;
  default:
    break;
  }
  if (dx != 0 || dy != 0)
  {
    engine.gameStatus = Engine::NEW_TURN;

    if (moveOrAttack(owner, owner->x + dx, owner->y + dy))
    {
      engine.map->computeFOV();
    }
  }
}

bool PlayerAi::moveOrAttack(Actor *owner, int targetX, int targetY)
{
  if (engine.map->isWall(targetX, targetY))
    return false;
  for (Actor **iterator = engine.actors.begin(); iterator != engine.actors.end(); iterator++)
  {
    Actor *actor = *iterator;
    if (actor->destructible && !actor->destructible->isDead() && actor->x == targetX && actor->y == targetY)
    {
      owner->attacker->attack(owner, actor);
      return false;
    }
  }
  for (Actor **iterator = engine.actors.begin(); iterator != engine.actors.end(); iterator++)
  {
    Actor *actor = *iterator;
    bool corpseOrItem = (actor->destructible && actor->destructible->isDead()) || actor->pickable;
    if (corpseOrItem && actor->x == targetX && actor->y == targetY)
    {
      engine.gui->message(TCODColor::lightGrey, "There's a %s here", actor->name);
    }
  }
  owner->x = targetX;
  owner->y = targetY;
  return true;
}

void PlayerAi::handleActionKey(Actor *owner, int keyCode)
{
  switch (keyCode)
  {
  case 'g':
  {
    bool found = false;
    for (Actor **iterator = engine.actors.begin(); iterator != engine.actors.end(); iterator++)
    {
      Actor *actor = *iterator;
      if (actor->pickable && actor->x == owner->x && actor->y == owner->y)
      {
        if (actor->pickable->pick(actor, owner))
        {
          found = true;
          engine.gui->message(TCODColor::lightGrey, "You pick up the %s", actor->name);
          break;
        }
        else if (!found)
        {
          found = true;
          engine.gui->message(TCODColor::red, "Your inventory is full.");
        }
      }
    }
    if (!found)
    {
      engine.gui->message(TCODColor::lightGrey, "There's nothing here to pick up.");
    }
    engine.gameStatus = Engine::NEW_TURN;
  }
  break;
  case 'i':
  {
    Actor *actor = chooseFromInventory(owner);
    if (actor)
    {
      actor->pickable->use(actor, owner);
      engine.gameStatus = Engine::NEW_TURN;
    }
  }
  break;
  }
}

Actor *PlayerAi::chooseFromInventory(Actor *owner)
{
  static const int INVENTORY_WIDTH = 50;
  static const int INVENTORY_HEIGHT = 28;
  static TCODConsole console(INVENTORY_WIDTH, INVENTORY_HEIGHT);
  console.setDefaultForeground(TCODColor(200, 180, 50));
  console.printFrame(0, 0, INVENTORY_WIDTH, INVENTORY_HEIGHT, true, TCOD_BKGND_DEFAULT, "inventory");

  console.setDefaultForeground(TCODColor::white);
  int shortcut = 'a';
  int y = 1;
  for (Actor **iterator = owner->container->inventory.begin(); iterator != owner->container->inventory.end(); iterator++)
  {
    Actor *actor = *iterator;
    console.print(2, y, "(%c) %s", shortcut, actor->name);
    y++;
    shortcut++;
  }
  TCODConsole::blit(&console, 0, 0, INVENTORY_WIDTH, INVENTORY_HEIGHT, TCODConsole::root, engine.screenWidth / 2 - INVENTORY_WIDTH / 2, engine.screenHeight / 2 - INVENTORY_HEIGHT / 2);
  TCODConsole::flush();

  TCOD_key_t key;
  TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, nullptr, true);
  if (key.vk == TCODK_CHAR)
  {
    int actorIndex = key.c - 'a';
    if (actorIndex >= 0 && actorIndex < owner->container->inventory.size())
    {
      return owner->container->inventory.get(actorIndex);
    }
  }
  return nullptr;
}

void MonsterAi::update(Actor *owner)
{
  if (owner->destructible->isDead())
  {
    return;
  }
  if (engine.map->isInFOV(owner->x, owner->y))
  {
    moveCount = TRACKING_TURNS;
  }
  else
  {
    moveCount--;
  }
  if (moveCount > 0)
  {
    moveOrAttack(owner, engine.player->x, engine.player->y);
  }
}

void MonsterAi::moveOrAttack(Actor *owner, int targetX, int targetY)
{
  int dx = targetX - owner->x;
  int dy = targetY - owner->y;
  int stepdx = (dx > 0 ? 1 : -1);
  int stepdy = (dx > 0 ? 1 : -1);
  float distance = sqrtf(dx * dx + dy * dy);
  if (distance >= 2)
  {
    dx = (int)(round(dx / distance));
    dy = (int)(round(dy / distance));
  }
  if (engine.map->canWalk(owner->x + dx, owner->y + dy))
  {
    owner->x += dx;
    owner->y += dy;
  }
  else if (engine.map->canWalk(owner->x + stepdx, owner->y))
  {
    owner->x += stepdx;
  }
  else if (engine.map->canWalk(owner->x, owner->y + stepdy))
  {
    owner->y += stepdy;
  }
  else if (owner->attacker)
  {
    owner->attacker->attack(owner, engine.player);
  }
}
