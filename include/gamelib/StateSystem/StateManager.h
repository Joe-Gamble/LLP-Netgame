//
// Created by miles on 28/03/2020.
//

#ifndef MYNETGAME_STATEMANAGER_H
#define MYNETGAME_STATEMANAGER_H

//#include <gamelib/StateSystem/Stat
#include <Engine/Input.h>
#include <vector>

enum GameState
{
  GS_NULL          = 0,
  GS_START_UP      = 1,
  GS_MENU          = 2,
  GS_LOBBY         = 3,
  GS_OPTIONS       = 4,
  GS_PARTY_MANAGER = 5,
  GS_IN_WORLD      = 6,
  GS_IN_BATTLE     = 7,
};

/// States must be forward declared to avoid circular dependancie
class MenuState;
class StartUpState;
class LobbyState;
class InWorldState;
class InBattleState;
class RenderData;
class GameData;
class State;
class NetworkCommunicator;

/// RAII + a stack
class StateManager
{
 public:
  explicit StateManager(GameData* _GD, RenderData* _RD, ASGE::Input* _input);
  //
  void init();
  void cleanUp();  /// used for a clean application quit

  StateManager* getSelf() { return this; }
  void changeState(int state);     /// used for changing the current game state
  void pushToStack(State* state);  /// useful for layering a new state on top of the current state
  State* getCurrentState()
  {
    if (!states.empty())
    {
      return states.back();
    }
  }
  void popFromStack();  /// ability to remove the back state and transition to the state below

  void updateState(GameData* _GD);
  void drawState(RenderData* _RD);

  State* stateLookUp(int enumState);

  RenderData* getRenderData();
  ASGE::Input* getInput();
  void setNetCom(NetworkCommunicator* _netComm) { p_netCom = _netComm; };
  NetworkCommunicator* getNetCom() { return p_netCom; };

 private:
  std::vector<State*> states;
  GameData* p_GD                = nullptr;
  RenderData* p_rd              = nullptr;
  ASGE::Input* p_input          = nullptr;
  NetworkCommunicator* p_netCom = nullptr;
};

#endif  // MYNETGAME_STATEMANAGER_H
