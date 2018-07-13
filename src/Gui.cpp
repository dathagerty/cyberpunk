#include <stdio.h>
#include <stdarg.h>
#include "main.hpp"

static const int PANEL_HEIGHT = 7;
static const int BAR_WIDTH = 20;
static const int MSG_X = BAR_WIDTH + 2;
static const int MSG_HEIGHT = PANEL_HEIGHT - 1;

Gui::Gui()
{
  screen = new TCODConsole(engine.screenWidth, PANEL_HEIGHT);
}

Gui::~Gui()
{
  delete screen;
  log.clearAndDelete();
}

void Gui::render()
{
  screen->setDefaultBackground(TCODColor::black);
  screen->clear();
  renderBar(1, 1, BAR_WIDTH, "HP", engine.player->destructible->currentHealth, engine.player->destructible->maxHealth, TCODColor::lightRed, TCODColor::darkerRed);
  int y = 1;
  float fadeAmount = 0.4f;
  for (Message **iterator = log.begin(); iterator != log.end(); iterator++)
  {
    Message *message = *iterator;
    screen->setDefaultForeground(message->color * fadeAmount);
    screen->print(MSG_X, y, message->text);
    y++;
    if (fadeAmount < 1.0f)
    {
      fadeAmount += 0.3f;
    }
  }
  renderMouseLook();
  TCODConsole::blit(screen, 0, 0, engine.screenWidth, PANEL_HEIGHT, TCODConsole::root, 0, engine.screenHeight - PANEL_HEIGHT);
}

void Gui::renderBar(int x, int y, int width, const char *name, float value, float maxValue, const TCODColor &barColor, const TCODColor &backColor)
{
  screen->setDefaultBackground(backColor);
  screen->rect(x, y, width, 1, false, TCOD_BKGND_SET);
  int barWidth = (int)(value / maxValue * width);
  if (barWidth > 0)
  {
    screen->setDefaultBackground(barColor);
    screen->rect(x, y, barWidth, false, TCOD_BKGND_SET);
  }
  screen->setDefaultForeground(TCODColor::white);
  screen->printEx(x + width / 2, y, TCOD_BKGND_NONE, TCOD_CENTER, "%s : %g/%g", name, value, maxValue);
}

void Gui::message(const TCODColor &color, const char *text, ...)
{
  va_list ap;
  char buf[128];
  va_start(ap, text);
  vsprintf(buf, text, ap);
  va_end(ap);
  char *lineBegin = buf;
  char *lineEnd;
  do
  {
    if (log.size() == MSG_HEIGHT)
    {
      Message *toRemove = log.get(0);
      log.remove(toRemove);
      delete toRemove;
    }
    lineEnd = strchr(lineBegin, '\n');
    if (lineEnd)
    {
      *lineEnd = '\0';
    }
    Message *msg = new Message(lineBegin, color);
    log.push(msg);
    lineBegin = lineEnd + 1;
  } while (lineEnd);
}

void Gui::renderMouseLook()
{
  if (!engine.map->isInFOV(engine.mouse.cx, engine.mouse.cy))
  {
    return;
  }
  char buf[128] = "";
  bool first = true;
  for (Actor **it = engine.actors.begin(); it != engine.actors.end(); it++)
  {
    Actor *actor = *it;
    if (actor->x == engine.mouse.cx && actor->y == engine.mouse.cy)
    {
      if (!first)
      {
        strcat(buf, ", ");
      }
      else
      {
        first = false;
      }
      strcat(buf, actor->name);
    }
  }
  screen->setDefaultForeground(TCODColor::lightGrey);
  screen->print(1, 0, buf);
}

Gui::Message::Message(const char *text, const TCODColor &color) : color(color)
{
  this->text = new char[strlen(text)];
  strcpy(this->text, text);
}

Gui::Message::~Message()
{
  delete[] text;
}
