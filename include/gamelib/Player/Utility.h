//
// Created by joemi on 27/04/2020.
//

#ifndef MYNETGAME_UTILITY_H
#define MYNETGAME_UTILITY_H
#include "Inventory.h"

class Utility : public Item
{
 public:
  Utility()  = default;
  ~Utility() = default;

  virtual void use();

 private:
 protected:
  bool self_use_only = false;
};

class Heal : public Utility
{
 public:
  Heal()  = default;
  ~Heal() = default;

  void initUtility(int _heal_amount, int _range, int _price);
  void use() override;

 private:
  int heal_amount = 0;
};
class Shield : public Utility
{
 public:
  Shield()  = default;
  ~Shield() = default;
  void initUtility(int _uses, int _range, int _price);

 private:
  int uses = 0;
};
class Mark : public Utility
{
 public:
  Mark()  = default;
  ~Mark() = default;
  void initUtility(float _multiplier, int _range, int _price);

 private:
  float multiplier = 0.0F;
};

#endif  // MYNETGAME_UTILITY_H
