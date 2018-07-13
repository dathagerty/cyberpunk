class Gui
{
public:
  Gui();
  ~Gui();
  void message(const TCODColor &color, const char *text, ...);
  void render();

protected:
  TCODConsole *screen;
  struct Message
  {
    char *text;
    TCODColor color;
    Message(const char *text, const TCODColor &color);
    ~Message();
  };
  TCODList<Message *> log;

  void renderBar(int x, int y, int width, const char *name, float value, float maxValue, const TCODColor &barColor, const TCODColor &backColor);
  void renderMouseLook();
};
