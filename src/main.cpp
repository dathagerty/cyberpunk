#include "main.hpp"

Engine engine(80, 50);

int main()
{
  while (!TCODConsole::isWindowClosed())
  {
    engine.update();
    engine.render();
    TCODConsole::flush();
  }
  return 0;
}
