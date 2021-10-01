//
// Created by miles on 31/03/2020.
//

#ifndef MYNETGAME_MENUSTATE_H
#define MYNETGAME_MENUSTATE_H

#include "State.hpp"

class MenuState : public State
{
 public:
  MenuState()          = default;
  virtual ~MenuState() = default;

  void enter() override;
  void exit() override;

  void update(GameData* _GD) override;
  void draw(RenderData* _RD) override;

  void pause() override;
  void resume() override;

 private:
};

#endif  // MYNETGAME_MENUSTATE_H
