struct Tile {
	bool canWalk; // if actors can move through the tile
	Tile() : canWalk(true) {}
};

class Map {
public:
	int width, height;

	Map(int width, int height);
	bool isWall(int x, int y) const;
	void render() const;
	~Map();

protected:
	Tile *tiles;

	void setWall(int x, int y);
	
};