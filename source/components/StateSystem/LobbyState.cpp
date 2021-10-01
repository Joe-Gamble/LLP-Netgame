//
// Created by miles on 05/04/2020.
//

#include "gamelib/StateSystem/LobbyState.h"

#include "gamelib/GameData.h"
#include "gamelib/RenderData.h"

void LobbyState::enter()
{
  state_id = 3;

  /// Make UI for this state
  UI = std::make_unique<UIManager>();
  UI->initialiseUI(this, p_manager->getInput());
}

void LobbyState::exit() {}

void LobbyState::update(GameData* _GD)
{
  if (UI)
  {
    UI->updateElements(_GD);
  }
}

void LobbyState::draw(RenderData* _RD)
{
  _RD->p_renderer->renderText("------In Lobby  State------", 400, 320);
  _RD->p_renderer->renderText(" ", 390, 350);

  if (UI)
  {
    UI->renderElements(_RD);
  }
}

void LobbyState::pause()
{
  paused = true;
}

void LobbyState::resume()
{
  paused = false;
}
