class Actor
{
public:
  int x, y;                   // x and y position on the map
  int character;              // ascii character code
  const char *name;           // the actor's name
  TCODColor color;            // character color, from TCOD
  bool blocks;                // does the actor block movement
  Attacker *attacker;         // damage source
  Destructible *destructible; // damage receiver
  Ai *ai;                     // handles updates for actors
  Pickable *pickable;         // an actor that can be picked up or used
  Container *container;       // a container for actors

  Actor(int x, int y, int character, const char *name, const TCODColor &color);
  bool moveOrAttack(int x, int y);
  float getDistance(int destX, int destY) const;
  void update();
  void render() const;
  ~Actor();
};
