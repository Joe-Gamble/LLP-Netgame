//
// Created by miles on 28/03/2020.
//

#ifndef MYNETGAME_STATE_HPP
#define MYNETGAME_STATE_HPP

#include "memory.h"

#include <gamelib/GameObject.hpp>
#include <gamelib/UISystem/UIManager.h>
#include <vector>

class Scene;
class StateManager;
class UIManager;
struct GameData;
struct RenderData;

class State
{
 public:
  virtual void enter() = 0;  /// Handles the initialization of the state
  virtual void exit()  = 0;  /// Handles the clean up of the state

  virtual void update(GameData* _GD) = 0;  /// Update for everything that makes the state
  virtual void draw(RenderData* _RD) = 0;  /// Renders all sprites within each state

  virtual void pause()  = 0;  /// State specific method for pausing everything within the state
  virtual void resume() = 0;  ///...likewise resume method specific to each state

  void assignManagers(StateManager* st_manager);
  void setScene(Scene* _scene) { scene = _scene; }
  Scene* getScene() { return scene; }

  void changeState(StateManager* st_manager, int state);  /// To call the change state method
  int getStateId();
  StateManager* getStateManager();
  UIManager* getUI();

 protected:
  std::unique_ptr<UIManager> UI = nullptr;
  int state_id                  = NULL;

  bool paused             = false;
  StateManager* p_manager = nullptr;
  Scene* scene            = nullptr;
};

#endif  // MYNETGAME_STATE_HPP
