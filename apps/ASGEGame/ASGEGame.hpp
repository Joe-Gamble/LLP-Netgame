//
// Created by huxy on 23/02/2020.
//

#ifndef NETGAME_ASGEGAME_HPP
#define NETGAME_ASGEGAME_HPP

#include "ASGEGame/Managers/GameManager.h"
#include "ASGEGame/Managers/SceneManager.hpp"
#include "gamelib/GameData.h"
#include "gamelib/GameVariables.h"
#include "gamelib/RenderData.h"
#include "gamelib/StateSystem/StateManager.h"

#include <Engine/OGLGame.h>
#include <gamelib/Components/GCNetClient.hpp>
#include <gamelib/Components/GCNetServer.hpp>
#include <gamelib/Components/GameComponent.hpp>
#include <gamelib/Sound/SoundManager.h>
#include <iostream>
#include <memory>
#include <soloud.h>
#include <soloud_wav.h>
#include <vector>

class Game : public ASGE::OGLGame
{
 public:
  explicit Game(const ASGE::GameSettings& settings);
  ~Game() override;

  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;

  void keyHandler(ASGE::SharedEventData data);
  void mouseHandler(ASGE::SharedEventData data);
  void clickHandler(ASGE::SharedEventData data);
  void scrollHandler(ASGE::SharedEventData data);

  void update(const ASGE::GameTime& us) override;
  void render() override;

 private:
  std::vector<GameComponent*> game_components;

  int mouse_callback_id      = -1; /**< Mouse Click Callback ID. */
  int mouse_move_callback_id = -1; /**< Mouse Move Callback ID. */
  int key_callback_id        = -1; /**< Key Input Callback ID. */

  std::unique_ptr<GameManager> gameManager;
  std::unique_ptr<NetworkCommunicator> netCommunicator;
  std::unique_ptr<StateManager> stateManager;
  GameData* m_GD;
  RenderData* m_RD;
  std::unique_ptr<SoundManager> soundManager;

  float const volumeChange = 0.2;
  float const damage       = 0.2;
};

#endif  // NETGAME_ASGEGAME_HPP
