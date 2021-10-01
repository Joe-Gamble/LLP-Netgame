//
// Created by miles on 28/03/2020.
//

#include "gamelib/StateSystem/State.hpp"

#include "gamelib/GameData.h"

void State::changeState(StateManager* st_manager, int state)
{
  st_manager->changeState(state);
}

void State::assignManagers(StateManager* st_manager)
{
  p_manager = st_manager;
}

StateManager* State::getStateManager()
{
  if (p_manager != nullptr)
  {
    return p_manager;
  }
  return nullptr;
}

UIManager* State::getUI()
{
  if (UI != nullptr)
  {
    return UI->getSelf();
  }
  return nullptr;
}

int State::getStateId()
{
  if (state_id != NULL)
  {
    return state_id;
  }
  return -1;
}
