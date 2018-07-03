class Actor
{
  public:
	int x, y;		  // x and y position on the map
	int character;	// ascii character code
	const char *name; // the actor's name
	TCODColor color;  // character color, from TCOD

	Actor(int x, int y, int character, const char *name, const TCODColor &color);
	bool moveOrAttack(int x, int y);
	void update();
	void render() const;
};