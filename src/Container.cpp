#include "main.hpp"

Container::Container(int size) : size(size) {}

Container::~Container() = default;

bool Container::add(Actor *item)
{
    if (size > 0 && inventory.size() >= size)
    {
        return false;
    }
    inventory.push(item);
    return true;
}

void Container::remove(Actor *item)
{
    inventory.remove(item);
}
