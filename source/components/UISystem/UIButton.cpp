//
// Created by miles on 05/04/2020.
//

#include "gamelib/UISystem/UIButton.h"

#include <gamelib/StateSystem/State.hpp>

UIButton::UIButton(
  float x,
  float y,
  float w,
  float h,
  std::string& texture,
  UIManager* _UIM,
  int gf_code)
{
  properties       = new UiProperties(x, y, w, h, texture);
  ui_manager       = _UIM;
  generic_function = gf_code;
}

UIButton::UIButton(float x, float y, float w, float h, std::string& texture, UIManager* _UIM)
{
  properties = new UiProperties(x, y, w, h, texture);

  ui_manager = _UIM;
}

UIStChangeBtn::UIStChangeBtn(
  float x,
  float y,
  float w,
  float h,
  std::string& texture,
  UIManager* _UIM,
  int state)
{
  properties   = new UiProperties(x, y, w, h, texture);
  ui_manager   = _UIM;
  state_change = state;
}

void UIButton::update(GameData* _GD) {}

void UIButton::render(RenderData* _RD)
{
  _RD->p_renderer->renderSprite(*spriteComponent()->getSprite());
}

void UIButton::onMouseOver()
{
  sprite_component->getSprite()->opacity(0.5);
  selected = true;
}

void UIButton::onMouseOut()
{
  selected = false;
  sprite_component->getSprite()->opacity(1.0);
}

void UIButton::onMouseClick()
{
  switch (generic_function)
  {
  case GF_OPTIONS:
  {
    //@todo implement options
    break;
  }
  case GF_QUIT:
  {
    GF_QUIT;  //@todo implement quit
    // ASGE::Game::signalExit(
    break;
  }
  case GF_CREATE_LOBBY:
  {
    CreateLobbyCmd::execute(*ui_manager->getNetComms(), 2);
    break;
  }
  case GF_JOIN_LOBBY:
  {
    JoinLobbyCmd::execute(*ui_manager->getNetComms(), 1);
    break;
  }
  case GF_SET_LOBBY_NAME:
  {
    SetLobbyNameCmd::execute(*ui_manager->getNetComms(), "SpankerLobby");
    break;
  }
  case GF_SEND_MESSAGE:
  {
    SendMessageCmd::execute(*ui_manager->getNetComms(), "Test Message");
    break;
  }
  case GF_GET_LOBBIES:
  {
    std::mutex mut_ex;
    mut_ex.lock();
    GetLobbiesCmd::execute(*ui_manager->getNetComms());
    mut_ex.unlock();
    break;
  }
  case GF_READY:
  {
    ReadyCmd::execute(*ui_manager->getNetComms());
    break;
  }
  case GF_UNREADY:
  {
    UnReadyCmd::execute(*ui_manager->getNetComms());
    break;
  }
  case GF_CLOSE_LOBBY:
  {
    CloseLobbyCmd::execute(*ui_manager->getNetComms());
    break;
  }
  case GF_OPEN_LOBBY:
  {
    OpenLobbyCmd::execute(*ui_manager->getNetComms());
    break;
  }
  case GF_KICK_PLAYER:
  {
    KickPlayer::execute(*ui_manager->getNetComms(), 1);
    break;
  }
  }
}

void UIStChangeBtn::changeState()
{
  ui_manager->changeState(state_change);
}

void UIStChangeBtn::onMouseClick()
{
  change_state = true;
}

void UIStChangeBtn::update(GameData* _GD)
{
  UIButton::update(_GD);
  if (change_state)
  {
    changeState();
  }
}
