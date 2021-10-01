//
// Created by miles on 05/04/2020.
//

#ifndef MYNETGAME_UIBUTTON_H
#define MYNETGAME_UIBUTTON_H

#include "gamelib/Command.h"
#include "gamelib/UISystem/UIObject.h"

#include <mutex>
enum GenericFunctions
{
  GF_NULL = 0,
  GF_OPTIONS,
  GF_QUIT,
  GF_JOIN_LOBBY     = 10,
  GF_CREATE_LOBBY   = 11,
  GF_SET_LOBBY_NAME = 12,
  GF_SEND_MESSAGE   = 13,
  GF_GET_LOBBIES    = 14,
  GF_READY          = 15,
  GF_UNREADY        = 16,
  GF_CLOSE_LOBBY    = 17,
  GF_OPEN_LOBBY     = 18,
  GF_KICK_PLAYER    = 19

};

class UIButton : public UIObject
{
 public:
  UIButton() = default;
  // explicit UIButton(float x, float y, float w, float h, const std::string text)

  UIButton(float x, float y, float w, float h, std::string& texture, UIManager* _UIM);
  UIButton(float x, float y, float w, float h, std::string& texture, UIManager* _UIM, int gf_code);

  ~UIButton() override = default;

  void update(GameData* _GD) override;
  void render(RenderData* _RD) override;

  void onMouseOver() override;
  void onMouseOut() override;
  void onMouseClick() override;

 protected:
  int generic_function = GF_NULL;

 private:
};

class UIStChangeBtn : public UIButton
{
 public:
  UIStChangeBtn(float x, float y, float w, float h, std::string& texture, UIManager* _UIM, int state);

  void update(GameData* _GD) override;
  void onMouseClick() override;

  void changeState();

 private:
  int state_change;
  bool change_state = false;
};

#endif  // MYNETGAME_UIBUTTON_H
