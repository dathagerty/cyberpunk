#include "libtcod.hpp"
#include "Actor.hpp"

Actor::Actor(int x, int y, int character, const TCODColor &color) :
    x(x), y(y), character(character), color(color) {
}

void Actor::render() const {
	TCODConsole::root->setChar(x, y, character);
	TCODConsole::root->setCharForeground(x, y, color);
}