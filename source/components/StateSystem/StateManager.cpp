//
// Created by miles on 28/03/2020.
//

#include <../apps/ASGEGame/Managers/SceneManager.hpp>
#include <gamelib/StateSystem/InBattleState.h>
#include <gamelib/StateSystem/InWorldState.h>
#include <gamelib/StateSystem/LobbyState.h>
#include <gamelib/StateSystem/MenuState.h>
#include <gamelib/StateSystem/OptionsState.h>
#include <gamelib/StateSystem/StartUpState.h>
#include <gamelib/StateSystem/StateManager.h>

StateManager::StateManager(GameData* _GD, RenderData* _RD, ASGE::Input* _input)
{
  p_GD    = _GD;
  p_rd    = _RD;
  p_input = _input;
}

/// Init all of the states to be used in the game
void StateManager::init()
{
  auto start_up_state = new StartUpState();
  states.push_back(start_up_state);
  start_up_state->assignManagers(this);
  states.back()->enter();
}

void StateManager::cleanUp()
{
  /// cleanup the all states - calling their exit functions
  while (!states.empty())
  {
    if (states.back()->getUI() != nullptr)
    {
      states.back()->getUI()->cleanUpUI(p_input);
    }
    states.back()->exit();
    states.pop_back();
  }
}

void StateManager::changeState(int enumState)
{
  Scene* scene = states.back()->getScene();

  /// exit the current state
  if (!states.empty())
  {
    if (states.back()->getUI() != nullptr)
    {
      states.back()->getUI()->cleanUpUI(p_input);
      states.back()->setScene(nullptr);
    }
    states.back()->exit();
    states.pop_back();
  }

  State* state = nullptr;

  switch (enumState)
  {
  case GS_MENU: state = new MenuState(); break;
  case GS_START_UP: state = new StartUpState(); break;
  case GS_OPTIONS: state = new OptionsState(); break;
  case GS_LOBBY: state = new LobbyState(); break;
  case GS_IN_WORLD: state = new InWorldState(); break;
  case GS_IN_BATTLE: state = new InBattleState(); break;
  default: break;
  }

  if (state == nullptr)
  {
    /// the state was not of this world
  }
  else
  {
    // push and enter the new state
    states.push_back(state);
    state->assignManagers(this);
    state->setScene(scene);
    states.back()->enter();
  }
}

void StateManager::pushToStack(State* state)
{
  /// pause current state
  if (!states.empty())
  {
    states.back()->pause();
  }
  else
  {
    /// store and init the new state
    states.push_back(state);
    state->assignManagers(this);
    states.back()->enter();
  }
}

void StateManager::popFromStack()
{
  /// exit the current state
  if (!states.empty())
  {
    if (states.back()->getUI() != nullptr)
    {
      states.back()->getUI()->cleanUpUI(p_input);
    }
    states.back()->exit();
    states.pop_back();
  }

  /// resume previous state
  if (!states.empty())
  {
    states.back()->resume();
  }
}

void StateManager::updateState(GameData* _GD)
{
  states.back()->update(_GD);
}

void StateManager::drawState(RenderData* _RD)
{
  states.back()->getScene()->render(_RD);
  states.back()->draw(_RD);
}

RenderData* StateManager::getRenderData()
{
  return p_rd;
}

ASGE::Input* StateManager::getInput()
{
  return p_input;
}
