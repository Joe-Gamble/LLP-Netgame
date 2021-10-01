//
// Created by miles on 05/04/2020.
//

#include "gamelib/StateSystem/OptionsState.h"

#include "gamelib/GameData.h"
#include "gamelib/RenderData.h"

void OptionsState::enter() {}

void OptionsState::exit() {}

void OptionsState::update(GameData* _GD) {}

void OptionsState::draw(RenderData* _RD)
{
  _RD->p_renderer->renderText("------In Options State------", 400, 320);
  _RD->p_renderer->renderText(" ", 390, 350);
}

void OptionsState::pause()
{
  paused = true;
}

void OptionsState::resume()
{
  paused = false;
}
