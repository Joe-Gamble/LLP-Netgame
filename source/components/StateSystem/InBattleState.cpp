//
// Created by miles on 05/04/2020.
//

#include "gamelib/StateSystem/InBattleState.h"

#include "gamelib/GameData.h"
#include "gamelib/RenderData.h"

void InBattleState::enter() {}

void InBattleState::exit() {}

void InBattleState::update(GameData* _GD) {}

void InBattleState::draw(RenderData* _RD)
{
  _RD->p_renderer->renderText("------In Battle State------", 400, 320);
  _RD->p_renderer->renderText(" ", 390, 350);
}

void InBattleState::pause()
{
  paused = true;
}

void InBattleState::resume()
{
  paused = false;
}