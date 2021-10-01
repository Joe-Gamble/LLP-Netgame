//
// Created by miles on 05/04/2020.
//

#include "gamelib/StateSystem/InWorldState.h"

#include "gamelib/GameData.h"
#include "gamelib/RenderData.h"

void InWorldState::enter() {}

void InWorldState::exit() {}

void InWorldState::update(GameData* _GD) {}

void InWorldState::draw(RenderData* _RD)
{
  _RD->p_renderer->renderText("------In World State------", 400, 320);
  _RD->p_renderer->renderText(" ", 390, 350);
}

void InWorldState::pause()
{
  paused = true;
}

void InWorldState::resume()
{
  paused = false;
}