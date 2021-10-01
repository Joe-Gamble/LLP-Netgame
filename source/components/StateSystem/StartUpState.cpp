//
// Created by miles on 30/03/2020.
//
#include "gamelib/StateSystem/StartUpState.h"

#include "gamelib/GameData.h"
#include "gamelib/RenderData.h"

void StartUpState::enter()
{
  state_id = 1;
}

void StartUpState::exit() {}

void StartUpState::update(GameData* _GD)
{
  if (_GD->m_kbs->key == ASGE::KEYS::KEY_RIGHT)
  {
    changeState(p_manager, GS_MENU);
  }
  if (_GD->m_kbs->key == ASGE::KEYS::KEY_P)
  {
    if (paused)
    {
      resume();
    }
    else
    {
      pause();
    }
  }
}

void StartUpState::draw(RenderData* _RD) {}

void StartUpState::pause()
{
  paused = true;
}

void StartUpState::resume()
{
  paused = false;
}
