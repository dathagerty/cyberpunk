class Ai
{
public:
  virtual void update(Actor *owner) = 0;
};

class PlayerAi : public Ai
{
public:
  void update(Actor *owner);

protected:
  void handleActionKey(Actor *owner, int keyCode);
  bool moveOrAttack(Actor *owner, int targetX, int targetY);
  Actor *chooseFromInventory(Actor *owner);
};

class MonsterAi : public Ai
{
public:
  void update(Actor *owner);

protected:
  int moveCount;

  void moveOrAttack(Actor *owner, int targetX, int targetY);
};

class ConfusedAi : public Ai
{
public:
  ConfusedAi(int numberOfTurns, Ai *oldAi);
  void update(Actor *owner);

protected:
  int numberOfTurns;
  Ai *oldAi;
};
