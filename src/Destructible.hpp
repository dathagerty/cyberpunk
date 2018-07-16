class Destructible
{
public:
  float maxHealth;
  float currentHealth;
  float defense;
  const char *corpseName;

  Destructible(float maxHealth, float defense, const char *corpseName);
  inline bool isDead() { return currentHealth <= 0; }
  float takeDamage(Actor *owner, float damage);
  float heal(float amount);
  virtual void die(Actor *owner);
};

class MonsterDestructible : public Destructible
{
public:
  MonsterDestructible(float maxHp, float defense, const char *corpseName);
  void die(Actor *owner);
};

class PlayerDestructible : public Destructible
{
public:
  PlayerDestructible(float maxHp, float defense, const char *corpseName);
  void die(Actor *owner);
};
