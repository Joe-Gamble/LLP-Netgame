//
// Created by miles on 30/03/2020.
//

#ifndef MYNETGAME_STARTUPSTATE_H
#define MYNETGAME_STARTUPSTATE_H

#include "State.hpp"

/**
 *  @brief StartUpState is the initial state that, displays the screen pre menu, press
 *  any button to continue to menu. The state should showcase some of the game.
 */

class StartUpState : public State
{
 public:
  StartUpState()          = default;
  virtual ~StartUpState() = default;

  /// initialize all scene sprites
  void enter() override;
  void exit() override;

  void update(GameData* _GD) override;
  void draw(RenderData* _RD) override;

  void pause() override;
  void resume() override;

 protected:
 private:
};

#endif  // MYNETGAME_STARTUPSTATE_H
