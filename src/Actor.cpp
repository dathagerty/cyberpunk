#include <stdio.h>
#include "main.hpp"

Actor::Actor(int x, int y, int character, const char *name, const TCODColor &color) : x(x), y(y), character(character), name(name), color(color), blocks(true), attacker(nullptr), destructible(nullptr), ai(nullptr)
{
}

bool Actor::moveOrAttack(int x, int y)
{

  if (engine.map->isWall(x, y))
  {
    return false;
  }

  for (Actor **iterator = engine.actors.begin(); iterator != engine.actors.end(); iterator++)
  {
    Actor *actor = *iterator;
    if (actor->x == x && actor->y == y)
    {
      printf("The %s laughs at your puny efforts to attack him!\n", actor->name);
      return false;
    }
  }
  this->x = x;
  this->y = y;
  return true;
}

void Actor::update()
{
  if (ai)
    ai->update(this);
}

void Actor::render() const
{
  TCODConsole::root->setChar(x, y, character);
  TCODConsole::root->setCharForeground(x, y, color);
}
