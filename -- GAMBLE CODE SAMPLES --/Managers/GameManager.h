//
// Joe Gamble - 26/03/20
//

#ifndef MYNETGAME_GAMEMANAGER_H
#define MYNETGAME_GAMEMANAGER_H

#include "NetworkCommunicator.h"
#include "SceneManager.hpp"
#include "gamelib/Lobby.h"
#include "nlohmann/json.hpp"

#include <Engine/FileIO.h>
#include <Engine/Game.h>
#include <Engine/Logger.hpp>
#include <gamelib/Handlers/TurnHandler.h>
#include <gamelib/Handlers/WeaponHandler.h>
#include <gamelib/Player/Entity.h>
#include <gamelib/Vector.hpp>

/**
 *  @brief GameManager sets up the scene for manipulation regarding positional data
 */

class GameManager
{
 public:
  GameManager() = default;
  explicit GameManager(RenderData* _RD, ASGE::Input* _input);
  ~GameManager() = default;

  GameManager* getSelf() { return this; }
  SceneManager* getSceneManager() { return &sceneManager; };
  TurnHandler* getTurnHandler() { return &turnHandler; }
  Player* getPlayer(int id) { return players.at(id - 1).get(); }
  std::vector<std::unique_ptr<Player>>* getPlayers() { return &players; }

  static nlohmann::json init(const std::string& file_name);
  void addPlayer(RenderData* _RD);

 private:
  SceneManager sceneManager;
  std::vector<std::unique_ptr<Player>> players;
  std::unique_ptr<Lobby> game_lobby;
  nlohmann::json game_data;
  TurnHandler turnHandler;
  RenderData* renderData = nullptr;
};

#endif  // MYNETGAME_GAMEMANAGER_H