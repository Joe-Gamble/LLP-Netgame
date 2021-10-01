//
// Joe Gamble - 23/04/2020
//

#include "gamelib/Handlers/WeaponHandler.h"

WeaponHandler::WeaponHandler()
{
  nlohmann::json weapon_data = init("Json/Weapondata");
  number_of_weapons          = weapon_data["Number_Of_Weapons"].get<int>();

  weapons.getObjects()->reserve(number_of_weapons);

  /// WEAPON SETUP

  Weapon* wand = new Wand();
  weapons.addObject(wand);
  Weapon* stick = new Stick();
  weapons.addObject(stick);
  Weapon* broad_sword = new BroadSword();
  weapons.addObject(broad_sword);
  Weapon* gun = new Gun();
  weapons.addObject(gun);

  int id = 0;
  for (auto& weapon : *getWeapons())
  {
    weapon.get().operator=(*createWeapon(dynamic_cast<Weapon*>(&weapon.get()), weapon_data, id));
    id++;
  }
}

Weapon* WeaponHandler::createWeapon(Weapon* _weapon, const nlohmann::json& data, int weapon_id)
{
  // retarget the json for the particular weapon
  nlohmann::json weapon_data = data["Weapons"][weapon_id];

  // store the desired variables
  auto name                         = weapon_data["name"].get<std::string>();
  _weapon->getData()->name          = name;
  auto filename                     = weapon_data["sprite"]["filename"].get<std::string>();
  _weapon->getData()->filename      = filename;
  _weapon->getItemStats()->itemType = WEAPON;

  return _weapon;
}

nlohmann::json WeaponHandler::init(const std::string& file_name)
{
  using File = ASGE::FILEIO::File;
  File file  = File();

  if (file.open(file_name + ".json"))
  {
    // load the file into a buffer object and convert into string
    using Buffer  = ASGE::FILEIO::IOBuffer;
    Buffer buffer = file.read();

    // parse the loaded string, you could
    nlohmann::json game_data =
      nlohmann::json::parse(buffer.as_char(), buffer.as_char() + buffer.length);

    file.close();
    return game_data;
  }
  Logging::ERRORS("Could not open file");
}