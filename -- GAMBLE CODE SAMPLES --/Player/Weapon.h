//
// Joe Gamble - 23/045/2020
//

#ifndef MYNETGAME_WEAPON_H
#define MYNETGAME_WEAPON_H

#include "Inventory.h"

class Weapon : public Item
{
 public:
  Weapon()  = default;
  ~Weapon() = default;
  void setDamage(float _damage) { damage = _damage; }
  float getDamage() { return damage; }

 protected:
  float damage = 0;
};

class Wand : public Weapon
{
 public:
  Wand()  = default;
  ~Wand() = default;

 private:
  std::string test = "test";
};
class Stick : public Weapon
{
 public:
  Stick()  = default;
  ~Stick() = default;

 private:
};
class BroadSword : public Weapon
{
 public:
  BroadSword()  = default;
  ~BroadSword() = default;

 private:
};
class Gun : public Weapon
{
 public:
  Gun()  = default;
  ~Gun() = default;

 private:
};

#endif  // MYNETGAME_WEAPON_H
