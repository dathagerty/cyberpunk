class Actor {
public:
	int x, y; // x and y position on the map
	int character; // ascii character code
	TCODColor color; // character color, from TCOD

	Actor(int x, int y, int character, const TCODColor &color);
	void render() const;
};