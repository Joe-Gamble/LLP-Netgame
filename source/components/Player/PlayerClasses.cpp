//
// Created by Acer on 30/04/2020.
//

#include "gamelib/Player/PlayerClasses.h"

void PlayerClasses::init(
  const std::string& name,
  const std::string& fileName,
  float health,
  float dodge,
  float speed)
{
  getData()->filename = fileName;
  getData()->name     = name;

  getEntityStats()->health = health;
  getEntityStats()->speed  = speed;
  getEntityStats()->dodge  = dodge;
}
