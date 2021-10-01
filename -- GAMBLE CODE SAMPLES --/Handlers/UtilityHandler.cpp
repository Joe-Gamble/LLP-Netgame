//
// Joe Gamble - 27/04/2020
//

#include "gamelib/Handlers/UtilityHandler.h"

UtilityHandler::UtilityHandler()
{
  nlohmann::json weapon_data = init("Json/Utilitydata");
  number_of_weapons          = weapon_data["Number_Of_Utility"].get<int>();

  utility_list.getObjects()->reserve(number_of_weapons);

  /// WEAPON SETUP

  Utility* heal = new Heal();
  utility_list.addObject(heal);
  Utility* shield = new Shield();
  utility_list.addObject(shield);
  Utility* mark = new Mark();
  utility_list.addObject(mark);

  int id = 0;
  for (auto& utility : *getUtilities())
  {
    utility.get().operator=(
      *createUtility(dynamic_cast<Utility*>(&utility.get()), weapon_data, id));
    id++;
  }
}

Utility*
UtilityHandler::createUtility(Utility* _utility, const nlohmann::json& data, int utility_id)
{
  // localise the pointer
  Utility* utility = _utility;

  // retarget the json for the particular weapon
  nlohmann::json utility_data = data["Utility"][utility_id];

  // store the desired variables
  auto name     = utility_data["name"].get<std::string>();
  auto filename = utility_data["sprite"]["filename"].get<std::string>();

  utility->getData()->filename = filename;
  utility->getData()->name     = name;

  auto type                    = UtilityList(utility_data["utility_type"].get<int>());
  nlohmann::json utility_stats = utility_data["stats"];

  int range = utility_stats["range"].get<int>();
  int price = utility_stats["price"].get<int>();

  // cast to the utility type in question
  switch (type)
  {
  case UtilityList ::HEAL:
  {
    auto* heal_utility = dynamic_cast<Heal*>(&getUtility(utility_id).get());
    int heal_amount    = utility_stats["heal_amount"].get<int>();
    heal_utility->initUtility(heal_amount, range, price);
    break;
  }
  case UtilityList ::SHIELD:
  {
    auto* heal_utility = dynamic_cast<Shield*>(&getUtility(utility_id).get());
    int uses           = utility_stats["uses"].get<int>();
    heal_utility->initUtility(uses, range, price);
    break;
  }
  case UtilityList ::MARK:
  {
    auto* heal_utility = dynamic_cast<Mark*>(&getUtility(utility_id).get());
    float multiplier   = utility_stats["multiplier"].get<int>();
    heal_utility->initUtility(multiplier, range, price);
    break;
  }
  default:
  {
    break;
  }
  }
  return utility;
}

nlohmann::json UtilityHandler::init(const std::string& file_name)
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