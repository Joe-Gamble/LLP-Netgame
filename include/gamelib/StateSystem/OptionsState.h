//
// Created by miles on 05/04/2020.
//

#ifndef MYNETGAME_OPTIONSSTATE_H
#define MYNETGAME_OPTIONSSTATE_H

#include "State.hpp"

class OptionsState : public State
{
 public:
  OptionsState()          = default;
  virtual ~OptionsState() = default;

  void enter() override;
  void exit() override;

  void update(GameData* _GD) override;
  void draw(RenderData* _RD) override;

  void pause() override;
  void resume() override;

 protected:
 private:
};

#endif  // MYNETGAME_OPTIONSSTATE_H
