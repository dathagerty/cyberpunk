class Engine
{
  public:
	TCODList<Actor *> actors;
	Actor *player;
	Map *map;
	int fovRadius;

	Engine();
	void update();
	void render();
	~Engine();

  private:
	bool computeFOV;
};

extern Engine engine;