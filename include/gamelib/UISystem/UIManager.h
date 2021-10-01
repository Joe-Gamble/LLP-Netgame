//
// Created by miles on 05/04/2020.
//

#ifndef MYNETGAME_UIMANAGER_H
#define MYNETGAME_UIMANAGER_H

#include "gamelib/Command.h"
#include "gamelib/UISystem/UIObject.h"
#include "nlohmann/json.hpp"

#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Point2D.h>
#include <atomic>
#include <mutex>
#include <thread>
#include <vector>

class NetworkCommunicator;
class UIStButton;
class UITextBox;
class UIButton;
class RenderData;
class GameData;
class UIObject;
class StateManager;
class State;

class UIManager
{
  enum EventType
  {
    CLICK = 0,
    MOUSE = 1
  };

 public:
  UIManager()  = default;
  ~UIManager() = default;

  UIManager(UIManager const&) = delete;
  UIManager& operator=(UIManager const&) = delete;
  UIManager(UIManager&&)                 = delete;
  UIManager& operator=(UIManager&&) = delete;

  void initialiseUI(State* _S, ASGE::Input* _input);  // Sets up the ui objects from json & links
                                                      // the state manager
  void cleanUpUI(ASGE::Input* _input);  // Clears out memory when the ui is no longer needed, also
                                        // unregisters callback

  void updateElements(GameData* _GD);
  void renderElements(RenderData* _RD);

  void changeState(int state_change);

  /// Refactoring to make use of callbacks
  void disableInput(ASGE::Input* input);
  void enableInput(ASGE::Input* input);
  UIObject* returnHandleEvent(const ASGE::Point2D& event_point, int event_type);

  UIManager* getSelf();
  void setNetComms(NetworkCommunicator* net_comm);
  NetworkCommunicator* getNetComms() { return net_comms; };
  UITextBox* getOutputTextBox()
  {
    if (outputBox != nullptr)
    {
      return outputBox;
    }
    return nullptr;
  };

 private:
  std::vector<UIObject*> ui_elements;    /// Container for all ui elements in use
  UIObject* selected_element = nullptr;  /// The local variable for resetting the selected element
  UITextBox* commandBox      = nullptr;  ///
  UITextBox* outputBox       = nullptr;

  /// Making use of the asge tutorial on menus
  bool isInside(ASGE::Sprite* btn, ASGE::Point2D point) const;
  bool loadFonts(ASGE::Renderer* renderer);
  std::mutex mutex_lock;

  static nlohmann::json loadUI(const std::string& file_name);
  void mouseHandler(ASGE::SharedEventData data);
  void clickHandler(ASGE::SharedEventData data);
  void keyHandler(ASGE::SharedEventData data);

  State* state                   = nullptr;
  StateManager* state_manager    = nullptr;  /// A pointer to state managers interface for changing
  NetworkCommunicator* net_comms = nullptr;  /// states

  ASGE::Sprite* cursor     = nullptr;
  ASGE::Point2D cursor_pos = {};

  int menu_font_index    = -1;
  int mouse_handler_idx  = -1;
  int mouse_click_handle = -1;
  int key_handler_index  = -1;
};

#endif  // MYNETGAME_UIMANAGER_H
