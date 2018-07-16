class Container
{
public:
  int size;
  TCODList<Actor *> inventory;

  Container(int size);
  ~Container();
  bool add(Actor *item);
  void remove(Actor *item);
};
