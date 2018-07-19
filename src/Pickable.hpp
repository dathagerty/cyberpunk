class Pickable
{
public:
  bool pick(Actor *owner, Actor *wearer);
  virtual bool use(Actor *owner, Actor *wearer);
  void drop(Actor *owner, Actor *wearer);
};

class Healer : public Pickable
{
public:
  float amount;

  Healer(float amount);
  bool use(Actor *owner, Actor *wearer);
};

class TargetedEmp : public Pickable
{
public:
  float range, damage;
  TargetedEmp(float range, float damage);
  bool use(Actor *owner, Actor *wearer);
};

class FragGrenade : public TargetedEmp
{
public:
  FragGrenade(float range, float damage);
  bool use(Actor *owner, Actor *wearer);
};

class TearGas : public Pickable
{
public:
  int numberOfTurns;
  float range;
  TearGas(int numberOfTurns, float range);
  bool use(Actor *owner, Actor *wearer);
};
