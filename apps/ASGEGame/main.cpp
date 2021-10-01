#include "../include/gamelib/GameVariables.h"
#include "ASGEGame.hpp"
#include "gamelib/GameVariables.h"

#include <Engine/GameSettings.hpp>
#include <Engine/Logger.hpp>

int main(int argc, char* argv[])
{
  ASGE::GameSettings game_settings;
  game_settings.window_width  = GameVariables::WINDOW_WITH;
  game_settings.window_height = GameVariables::WINDOW_HEIGHT;
  game_settings.mode          = ASGE::GameSettings::WindowMode::WINDOWED;
  game_settings.anisotropic   = GameVariables::ANISOTROPIC;
  game_settings.msaa_level    = 1;

  Logging::INFO("Launching Game!");
  Game game(game_settings);

  game.run();

  return 0;
}