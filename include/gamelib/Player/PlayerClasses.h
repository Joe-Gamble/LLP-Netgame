//
// Created by Acer on 30/04/2020.
//

#ifndef MYNETGAME_PLAYERCLASSES_H
#define MYNETGAME_PLAYERCLASSES_H

#include <gamelib/Player/Entity.h>

class PlayerClasses : public Player
{
 public:
  ~PlayerClasses() = default;

  void
  init(const std::string& name, const std::string& fileName, float health, float dodge, float speed);
};

class Mage : public PlayerClasses
{
 public:
  ~Mage() = default;
};

class Warrior : public PlayerClasses
{
 public:
  ~Warrior() = default;
};

class Rogue : public PlayerClasses
{
 public:
  ~Rogue() = default;
};

#endif  // MYNETGAME_PLAYERCLASSES_H
