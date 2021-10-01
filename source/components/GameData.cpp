//
// Created by miles on 28/03/2020.
//

#include "gamelib/GameData.h"

GameData::GameData() :
  m_kbs(new ASGE::KeyEvent),
  m_clk(new ASGE::ClickEvent),
  m_ms(new ASGE::MoveEvent)
{
}

GameData::~GameData()
{
  delete m_ms;
  m_ms = nullptr;

  delete m_clk;
  m_clk = nullptr;

  delete m_kbs;
  m_kbs = nullptr;
}

void GameData::setKD(const ASGE::KeyEvent* data)
{
  m_kbs->key      = data->key;
  m_kbs->scancode = data->scancode;
  m_kbs->action   = data->action;
  m_kbs->mods     = data->mods;
}

void GameData::setCD(const ASGE::ClickEvent* data)
{
  m_clk->mods   = data->mods;
  m_clk->action = data->action;
  m_clk->button = data->button;
  m_clk->xpos   = data->xpos;
  m_clk->ypos   = data->ypos;
}

void GameData::setMD(const ASGE::MoveEvent* data)
{
  m_ms->xpos = data->xpos;
  m_ms->ypos = data->ypos;
}

void GameData::resetCD()
{
  m_clk->mods   = -1;
  m_clk->action = -1;
  m_clk->button = -1;
  m_clk->xpos   = -1;
  m_clk->ypos   = -1;
}
