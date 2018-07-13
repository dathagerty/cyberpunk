#include "main.hpp"

Attacker::Attacker(float power) : power(power) {}

void Attacker::attack(Actor *owner, Actor *target)
{
  float damage = power - target->destructible->defense;
  if (!target->destructible->isDead())
  {
    if (damage > 0)
    {
      engine.gui->message(owner == engine.player ? TCODColor::red : TCODColor::lightGrey, "%s attacks %s for %g hit points.", owner->name, target->name, damage);
    }
    else
    {
      engine.gui->message(TCODColor::lightGrey, "%s attacks %s but it has no effect!", owner->name, target->name);
    }
    target->destructible->takeDamage(target, power);
  }
  else
  {
    engine.gui->message(TCODColor::lightGrey, "%s attacks %s in vain.", owner->name, target->name);
  }
}
