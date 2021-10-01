//
// Created by miles on 05/04/2020.
//

#ifndef MYNETGAME_INBATTLESTATE_H
#define MYNETGAME_INBATTLESTATE_H

#include "State.hpp"

class InBattleState : public State
{
 public:
  InBattleState()          = default;
  virtual ~InBattleState() = default;

  void enter() override;
  void exit() override;

  void update(GameData* _GD) override;
  void draw(RenderData* _RD) override;

  void pause() override;
  void resume() override;

 protected:
 private:
};

#endif  // MYNETGAME_INBATTLESTATE_H
