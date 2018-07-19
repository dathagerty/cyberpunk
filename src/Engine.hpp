class Engine
{
public:
  enum GameStatus
  {
    STARTUP,
    IDLE,
    NEW_TURN,
    VICTORY,
    DEFEAT
  } gameStatus;
  TCODList<Actor *> actors;
  Actor *player;
  Map *map;
  int fovRadius;
  int screenWidth;
  int screenHeight;
  Gui *gui;
  TCOD_key_t lastKey;
  TCOD_mouse_t mouse;

  Engine(int screenWidth, int screenHeight);
  void sendToBack(Actor *actor);
  Actor *getClosestMonster(int x, int y, float range) const;
  bool pickATile(int *x, int *y, float maxRange = 0.0f);
  Actor *getActor(int x, int y) const;
  void update();
  void render();
  ~Engine();
};

extern Engine engine;
