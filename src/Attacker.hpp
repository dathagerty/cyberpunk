class Attacker
{
public:
  float power; // damage dealt by Attacker

  Attacker(float power);
  void attack(Actor *owner, Actor *target);
};
