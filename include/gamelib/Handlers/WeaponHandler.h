//
// Created by joemi on 23/04/2020.
//

#ifndef MYNETGAME_WEAPONHANDLER_H
#define MYNETGAME_WEAPONHANDLER_H

#include <Engine/FileIO.h>
#include <Engine/Logger.hpp>
#include <gamelib/Player/Weapon.h>
#include <nlohmann/json.hpp>
#include <vector>

class WeaponHandler
{
  enum WeaponList
  {
    WAND       = 0,
    STICK      = 1,
    BROADSWORD = 2,
    GUN        = 3
  };

 public:
  WeaponHandler();
  ~WeaponHandler() = default;

  static nlohmann::json init(const std::string& file_name);
  static Weapon* createWeapon(Weapon* _weapon, const nlohmann::json& data, int weapon_id);

  const std::vector<std::reference_wrapper<SceneObject>>* getWeapons()
  {
    return weapons.getObjects();
  }

  std::reference_wrapper<SceneObject> getWeapon(int id) { return weapons.getObjects()->at(id); }

  ObjectPool* getPool() { return &weapons; }

 private:
  ObjectPool weapons;
  int number_of_weapons = 0;
};
#endif  // MYNETGAME_WEAPONHANDLER_H