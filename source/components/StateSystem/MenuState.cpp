//
// Created by miles on 31/03/2020.
//

#include "gamelib/StateSystem/MenuState.h"

#include "gamelib/GameData.h"
#include "gamelib/RenderData.h"

void MenuState::enter()
{
  state_id                         = 2;
  std::unique_ptr<GameObject> logo = std::make_unique<GameObject>();
  logo->instantiate(
    p_manager->getRenderData()->p_renderer, "data/CustomUI/MenuLogo.png", 450, 40, 360, 280);

  /// Make the UI for this state
  UI = std::make_unique<UIManager>();
  UI->initialiseUI(this, p_manager->getInput());
}

void MenuState::exit() {}

void MenuState::update(GameData* _GD)
{
  if (UI)
  {
    UI->updateElements(_GD);
  }
}

void MenuState::draw(RenderData* _RD)
{
  _RD->p_renderer->renderText("------In Main Menu State------", 400, 320);
  _RD->p_renderer->renderText(" ", 390, 350);

  if (UI)
  {
    UI->renderElements(_RD);
  }
}

void MenuState::pause()
{
  paused = true;
}

void MenuState::resume()
{
  paused = false;
}
