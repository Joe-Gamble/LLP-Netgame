//
// Created by miles on 27/04/2020.
//

#ifndef MYNETGAME_NETWORKCOMMUNICATOR_H
#define MYNETGAME_NETWORKCOMMUNICATOR_H

#include "gamelib/Command.h"

#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <vector>

class GameManager;
class StateManager;
class SceneManager;
class GCNetClient;

struct ManagerAccessors
{
 public:
  ManagerAccessors(GameManager* _gm, StateManager* _st)
  {
    gameManager  = _gm;
    stateManager = _st;
  }

  GameManager* getGM()
  {
    if (gameManager != nullptr)
    {
      return gameManager;
    }
    return nullptr;
  };
  StateManager* getSM()
  {
    if (stateManager != nullptr)
    {
      return stateManager;
    }
    return nullptr;
  };

 private:
  GameManager* gameManager   = nullptr;
  StateManager* stateManager = nullptr;
  // SceneManager* sceneManager;
};

/// Command Type is the first letter of the string
enum CommandType
{
  UNDEFINED_CMD = 0,
  LOBBY_CMD     = 1,
  WORLD_CMD     = 2,
  BATTLE_CMD    = 3,
};

struct CommandStruct
{
  int command_type;
  int command_id;
  int entity_id;
  int data_a;  /// As this game isnt going to be too complicated each command only takes
  int data_b;  /// a maximum of 2 different data
};

class NetworkCommunicator
{
 public:
  NetworkCommunicator()  = default;
  ~NetworkCommunicator() = default;

  void init(GCNetClient* _client, GameManager* _gm, StateManager* _st);
  void debugPrint(const std::string& str);

  /// Getters
  NetworkCommunicator* getSelf() { return this; };
  GCNetClient* getNetClient()
  {
    if (client != nullptr)
    {
      return client;
    }
  };

  /// Sending & Receiving Commands
  void deserializeMessage(std::vector<char> data);
  void deserializeMessage(const std::string& cmd_stream);
  void serializeMessage(CommandStruct cmd);
  std::string padTypeOrId(int unpad_data);
  std::string padIntData(int unpad_data);

  void messageParser(const std::string& msg);
  void commandParser(CommandStruct cmd);

  void setUIServerOutput(const std::string& str);

 private:
  std::unique_ptr<ManagerAccessors> managers;
  std::mutex mut_ex;
  GCNetClient* client = nullptr;

  ///  Lobby Commands
  /* CreateLobbyCmd createLobbyCmd = nullptr;
   JoinLobbyCmd joinLobbyCmd = nullptr;
   SetLobbyNameCmd setLobbyNameCmd = nullptr;
   SendMessageCmd sendMessageCmd = nullptr;
   GetLobbiesCmd getLobbiesCmd = nullptr;
   ReadyCmd readyCmd = nullptr;
   UnReadyCmd unReadyCmd = nullptr;
   CloseLobbyCmd closeLobbyCmd = nullptr;
   OpenLobbyCmd openLobbyCmd = nullptr;
   KickPlayer kickPlayer = nullptr;
 */
};

#endif  // MYNETGAME_NETWORKCOMMUNICATOR_H
