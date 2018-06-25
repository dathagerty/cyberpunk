class Engine {
public:
	TCODList<Actor *> actors;
	Actor *player;
	Map *map;

	Engine();
	void update();
	void render();
	~Engine();
};

extern Engine engine;