//
// Created by miles on 05/04/2020.
//

#ifndef MYNETGAME_INWORLDSTATE_H
#define MYNETGAME_INWORLDSTATE_H

#include "State.hpp"

class InWorldState : public State
{
 public:
  InWorldState()          = default;
  virtual ~InWorldState() = default;

  void enter() override;
  void exit() override;

  void update(GameData* _GD) override;
  void draw(RenderData* _RD) override;

  void pause() override;
  void resume() override;

 protected:
 private:
};

#endif  // MYNETGAME_INWORLDSTATE_H
