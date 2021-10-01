//
// Created by joemi on 27/04/2020.
//

#include "gamelib/Player/Utility.h"

#include <Engine/Logger.hpp>

void Heal::initUtility(int _heal_amount, int _range, int _price)
{
  heal_amount        = _heal_amount;
  itemStats.itemType = ItemType::UTILITY;
  itemStats.range    = _range;
  itemStats.price    = _price;
}

void Shield::initUtility(int _uses, int _range, int _price)
{
  uses               = _uses;
  itemStats.itemType = ItemType::UTILITY;
  itemStats.range    = _range;
  self_use_only      = true;
  itemStats.price    = _price;
}

void Mark::initUtility(float _multiplier, int _range, int _price)
{
  multiplier         = _multiplier;
  itemStats.itemType = ItemType::UTILITY;
  itemStats.range    = _range;
  itemStats.price    = _price;
}

void Heal::use()
{
  Logging::INFO("HEAL");
}

void Utility::use() {}
