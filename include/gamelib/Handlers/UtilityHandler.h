//
// Created by joemi on 27/04/2020.
//

#ifndef MYNETGAME_UTILITYHANDLER_H
#define MYNETGAME_UTILITYHANDLER_H

#include <Engine/FileIO.h>
#include <Engine/Logger.hpp>
#include <gamelib/Player/Utility.h>
#include <nlohmann/json.hpp>
#include <vector>

class UtilityHandler
{
  enum UtilityList
  {
    HEAL   = 0,
    SHIELD = 1,
    MARK   = 2,
  };

 public:
  UtilityHandler();
  ~UtilityHandler() = default;

  static nlohmann::json init(const std::string& file_name);
  Utility* createUtility(Utility* _utility, const nlohmann::json& data, int utility_id);

  const std::vector<std::reference_wrapper<SceneObject>>* getUtilities()
  {
    return utility_list.getObjects();
  }

  std::reference_wrapper<SceneObject> getUtility(int id)
  {
    return utility_list.getObjects()->at(id);
  }
  ObjectPool* getPool() { return &utility_list; }

 private:
  ObjectPool utility_list;
  int number_of_weapons = 0;
};
#endif  // MYNETGAME_UTILITYHANDLER_H
