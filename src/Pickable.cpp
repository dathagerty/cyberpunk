#include "main.hpp"

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
