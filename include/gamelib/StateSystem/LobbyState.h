//
// Created by miles on 05/04/2020.
//

#ifndef MYNETGAME_LOBBYSTATE_H
#define MYNETGAME_LOBBYSTATE_H

#include "State.hpp"

class LobbyState : public State
{
 public:
  LobbyState()          = default;
  virtual ~LobbyState() = default;

  void enter() override;
  void exit() override;

  void update(GameData* _GD) override;
  void draw(RenderData* _RD) override;

  void pause() override;
  void resume() override;

 protected:
 private:
};

#endif  // MYNETGAME_LOBBYSTATE_H
