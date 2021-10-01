//
// Created by miles on 28/03/2020.
//

#ifndef MYNETGAME_GAMEDATA_H
#define MYNETGAME_GAMEDATA_H

#include "Engine/OGLGame.h"

#include <gamelib/StateSystem/StateManager.h>

/// Data to be used by all GameObjects through update

struct GameData
{
  GameData();
  ~GameData();
  GameData(GameData const&) = delete;
  GameData& operator=(GameData const&) = delete;
  GameData(GameData&&)                 = delete;
  GameData& operator=(GameData&&) = delete;

  // test

  void setKD(const ASGE::KeyEvent* data);
  void setCD(const ASGE::ClickEvent* data);
  void setMD(const ASGE::MoveEvent* data);
  double m_dt    = NULL;
  GameState m_gs = GS_NULL;
  void resetCD();

  ASGE::KeyEvent* m_kbs   = nullptr;
  ASGE::ClickEvent* m_clk = nullptr;
  ASGE::MoveEvent* m_ms   = nullptr;
};

#endif  // MYNETGAME_GAMEDATA_H
