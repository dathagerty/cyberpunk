#include "main.hpp"

static const float FRAG_GRENADE_RADIUS = 3;

bool Pickable::pick(Actor *owner, Actor *wearer)
{
    if (wearer->container->add(owner))
    {
        engine.actors.remove(owner);
        return true;
    }
    return false;
}

bool Pickable::use(Actor *owner, Actor *wearer)
{
    if (wearer->container)
    {
        wearer->container->remove(owner);
        delete owner;
        return true;
    }
    return false;
}

void Pickable::drop(Actor *owner, Actor *wearer)
{
    if (wearer->container)
    {
        wearer->container->remove(owner);
        engine.actors.push(owner);
        owner->x = wearer->x;
        owner->y = wearer->y;
        engine.gui->message(TCODColor::lightGrey, "%s drops a %s.", wearer->name, owner->name);
    }
}

Healer::Healer(float amount) : amount(amount)
{
}

bool Healer::use(Actor *owner, Actor *wearer)
{
    if (wearer->destructible)
    {
        float amountHealed = wearer->destructible->heal(amount);
        if (amountHealed > 0)
        {
            return Pickable::use(owner, wearer);
        }
    }
    return false;
}

TargetedEmp::TargetedEmp(float range, float damage) : range(range), damage(damage) {}

bool TargetedEmp::use(Actor *owner, Actor *wearer)
{
    Actor *closestMonster = engine.getClosestMonster(wearer->x, wearer->y, range);
    if (!closestMonster)
    {
        engine.gui->message(TCODColor::lightGrey, "No enemy is in range.");
        return false;
    }
    engine.gui->message(TCODColor::lightBlue, "The %s is hit by a targeted EMP blast for %g damage!", closestMonster->name, damage);
    closestMonster->destructible->takeDamage(closestMonster, damage);
    return Pickable::use(owner, wearer);
}

FragGrenade::FragGrenade(float range, float damage) : TargetedEmp(range, damage) {}

bool FragGrenade::use(Actor *owner, Actor *wearer)
{
    engine.gui->message(TCODColor::cyan, "Left-click a target tile.");
    int x, y;
    if (!engine.pickATile(&x, &y, range))
    {
        return false;
    }
    engine.gui->message(TCODColor::orange, "The grenade explodes, damaging everything within %g tiles!", FRAG_GRENADE_RADIUS);
    for (Actor **iterator = engine.actors.begin(); iterator != engine.actors.end(); iterator++)
    {
        Actor *actor = *iterator;
        if (actor->destructible && !actor->destructible->isDead() && actor->getDistance(x, y) < FRAG_GRENADE_RADIUS)
        {
            engine.gui->message(TCODColor::orange, "The %s gets damaged for %g hit points.", actor->name, damage);
            actor->destructible->takeDamage(actor, damage);
        }
    }
    return Pickable::use(owner, wearer);
}

TearGas::TearGas(int numberOfTurns, float range) : numberOfTurns(numberOfTurns), range(range) {}

bool TearGas::use(Actor *owner, Actor *wearer)
{
    engine.gui->message(TCODColor::cyan, "Left-click an enemy to target.");
    int x, y;
    if (!engine.pickATile(&x, &y, range))
    {
        return false;
    }
    Actor *actor = engine.getActor(x, y);
    if (!actor)
    {
        return false;
    }
    Ai *confusedAi = new ConfusedAi(numberOfTurns, actor->ai);
    actor->ai = confusedAi;
    engine.gui->message(TCODColor::lightGreen, "The %s stumbles around blindly.", actor->name);
    return Pickable::use(owner, wearer);
}
