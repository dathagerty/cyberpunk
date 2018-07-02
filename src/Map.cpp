#include "libtcod.hpp"
#include "Map.hpp"
#include "Actor.hpp"
#include "Engine.hpp"

static const int ROOM_MAX_SIZE = 10;
static const int ROOM_MIN_SIZE = 6;

class BspListener : public ITCODBspCallback {
private:
	Map &map;
	int roomNum;
	int lastX, lastY;

public:
	BspListener(Map &map) : map(map), roomNum(0) {}

	bool visitNode(TCODBsp *node, void *userData) {
		if (node->isLeaf()) {
			int x, y, w, h;
			TCODRandom *rng = TCODRandom::getInstance();
			w = rng->getInt(ROOM_MIN_SIZE, node->w - 2);
			h = rng->getInt(ROOM_MIN_SIZE, node->h - 2);
			x = rng->getInt(node->x + 1, node->x + node->w - w - 1);
			y = rng->getInt(node->y + 1, node->y + node->h - h - 1);
			map.createRoom(roomNum == 0, x, y, x + w - 1, y + h - 1);
			if (roomNum != 0) {
				map.dig(lastX, lastY, x + w/2, lastY);
				map.dig(x + w/2, lastY, x + w/2, y + h/2);
			}
			lastX = x + w/2;
			lastY = y + h/2;
			roomNum++;
		}
		return true;
	}
};

Map::Map(int width, int height) : width(width), height(height) {
	tiles = new Tile[width*height];
	TCODBsp bsp(0, 0, width, height);
	bsp.splitRecursive(NULL, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f, 1.5f);
	BspListener listener(*this);
	bsp.traverseInvertedLevelOrder(&listener, NULL);
}

bool Map::isWall(int x, int y) const {
	return !tiles[x+y*width].canWalk;
}

void Map::dig(int x1, int y1, int x2, int y2) {
	if (x2 < x1) {
		int temporary = x2;
		x2 = x1;
		x1 = temporary;
	}

	if (y2 < y1) {
		int temporary = y2;
		y2 = y1;
		y1 = temporary;
	}

	for (int tileX = x1; tileX <= x2; tileX++) {
		for (int tileY = y1; tileY <= y2; tileY++) {
			tiles[tileX + tileY * width].canWalk = true;
		}
	}
}

void Map::createRoom(bool first, int x1, int y1, int x2, int y2) {
	dig(x1, y1, x2, y2);
	if (first) {
		engine.player->x = (x1+x2)/2;
		engine.player->y = (y1+y2)/2;
	} else {
		TCODRandom *rng = TCODRandom::getInstance();
		if (rng->getInt(0,3) == 0) {
			engine.actors.push(new Actor((x1+x2)/2, (y1+y2)/2, '@', TCODColor::yellow));
		}
	}
}

void Map::render() const {
	static const TCODColor darkWall(0, 0, 100);
	static const TCODColor darkGround(50, 50, 150);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++)
		{
			TCODConsole::root->setCharBackground(x, y, isWall(x, y) ? darkWall : darkGround);
		}
	}
}

Map::~Map() {
	delete [] tiles;
}