struct Tile
{
  bool explored;
  Tile() : explored(false) {}
};

class Map
{
public:
  int width, height;

  Map(int width, int height);
  bool isWall(int x, int y) const;
  bool isInFOV(int x, int y) const;
  bool isExplored(int x, int y) const;
  bool canWalk(int x, int y) const;
  void computeFOV();
  void render() const;
  ~Map();

protected:
  Tile *tiles;
  TCODMap *map;
  friend class BspListener;

  void addMonster(int x, int y);
  void addItem(int x, int y);
  void dig(int x1, int y1, int x2, int y2);
  void createRoom(bool first, int x1, int y1, int x2, int y2);
};
