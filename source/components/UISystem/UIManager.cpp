//
// Created by miles on 05/04/2020.
//

#include "gamelib/UISystem/UIManager.h"

#include "gamelib/StateSystem/StateManager.h"
#include "gamelib/UISystem/UIButton.h"
#include "gamelib/UISystem/UITextBox.h"

#include <Engine/FileIO.h>
#include <Engine/Font.h>
#include <Engine/Logger.hpp>
#include <Engine/Sprite.h>
#include <gamelib/StateSystem/State.hpp>

/// Initialise each object for state from JSON & sets up the Managers + Text input
void UIManager::initialiseUI(State* _S, ASGE::Input* _input)
{
  enableInput(_input);
  state         = _S;
  state_manager = _S->getStateManager();
  net_comms     = state_manager->getNetCom();

  auto state_id          = _S->getStateId();  /// The state we are loading the ui into
  nlohmann::json ui_data = loadUI("/Json/UIData");
  auto state_count       = ui_data["Game"]["Num Of States"].get<int>();
  int ui_element_count   = ui_data["Game"]["States"][state_id]["Num Of Elements"].get<int>();

  if (ui_element_count > 0)
  {
    /// For each ui element in the json for said state
    for (int i = 0; i < ui_element_count; i++)
    {
      nlohmann::json state_data = ui_data["Game"]["States"][state_id]["Elements"][i];
      auto name                 = state_data["Name"].get<std::string>();
      auto ui_type              = state_data["UIType"].get<std::string>();
      auto ui_custom_data_a     = state_data["Type Custom Data"]["Data 1"][1].get<int>();
      auto ui_custom_data_b     = state_data["Type Custom Data"]["Data 2"][1].get<int>();

      nlohmann::json custom_data = state_data["Type Custom Data"];

      auto x = custom_data["UIProperties"]["X"].get<float>();
      auto y = custom_data["UIProperties"]["Y"].get<float>();
      auto h = custom_data["UIProperties"]["H"].get<float>();
      auto w = custom_data["UIProperties"]["W"].get<float>();

      auto file_path = custom_data["UIProperties"]["File Path"].get<std::string>();

      //@todo this code can be changed to UIType enum Codes in the Json, keeping the string types as

      if (ui_type == "UIStChangeBtn")
      {
        UIObject* name = new UIStChangeBtn(x, y, w, h, file_path, this, ui_custom_data_a);
        mutex_lock.lock();
        name->initSprite(state_manager->getRenderData()->p_renderer);
        mutex_lock.unlock();
        ui_elements.emplace_back(name);
      }
      else if (ui_type == "UIButton")
      {
        mutex_lock.lock();
        UIObject* name = new UIButton(x, y, w, h, file_path, this, ui_custom_data_a);
        name->initSprite(state_manager->getRenderData()->p_renderer);
        mutex_lock.unlock();
        ui_elements.emplace_back(name);
      }
      else
      {
        /// Undefined UIType
      }
    }
  }
  if (state_id == GS_LOBBY)
  {
    /// Text Input for chat messages and command input
    std::string s = "data/UIAssets/PNG/buttonLong_beige.png";
    commandBox    = new UITextBox(150, 560, 420, 50, s, this, INPUT_);
    commandBox->initSprite(state_manager->getRenderData()->p_renderer);
    std::string outp_file_path = "data/UIAssets/PNG/panel_beigeLight.png";
    outputBox                  = new UITextBox(150, 20, 420, 500, outp_file_path, this, OUTPUT);
    outputBox->initSprite(state_manager->getRenderData()->p_renderer);
  }
}

void UIManager::cleanUpUI(ASGE::Input* _inputs)
{
  if (!ui_elements.empty())
  {
    for (auto& ui_element : ui_elements)
    {
      delete ui_element->spriteComponent();
      ui_element = nullptr;
    }
  }

  if (commandBox != nullptr)
  {
    delete commandBox->spriteComponent();
    commandBox = nullptr;
  }

  if (outputBox != nullptr)
  {
    delete outputBox->spriteComponent();
    outputBox = nullptr;
  }

  disableInput(_inputs);
}

void UIManager::updateElements(GameData* _GD)
{
  if (!ui_elements.empty())
  {
    for (auto& ui_element : ui_elements)
    {
      if (ui_element != nullptr)
      {
        ui_element->update(_GD);
      }
    }
  }

  if (commandBox != nullptr)
  {
    commandBox->update(_GD);
  }
  if (outputBox != nullptr)
  {
    outputBox->update(_GD);
  }
}

void UIManager::renderElements(RenderData* _RD)
{
  if (!ui_elements.empty())
  {
    for (auto& ui_element : ui_elements)
    {
      if (ui_element != nullptr)
      {
        ui_element->render(_RD);
      }
    }
  }

  if (commandBox != nullptr)
  {
    commandBox->render(_RD);
  }
  if (outputBox != nullptr)
  {
    outputBox->render(_RD);
  }
}

void UIManager::clickHandler(ASGE::SharedEventData data)
{
  auto event = dynamic_cast<const ASGE::ClickEvent*>(data.get());
  ASGE::Point2D mouse_pos{float(event->xpos), float(event->ypos)};

  mutex_lock.lock();
  returnHandleEvent(mouse_pos, CLICK);
  mutex_lock.unlock();
}

void UIManager::mouseHandler(ASGE::SharedEventData data)
{
  auto event = dynamic_cast<const ASGE::MoveEvent*>(data.get());
  ASGE::Point2D mouse_pos{float(event->xpos), float(event->ypos)};

  selected_element = returnHandleEvent(mouse_pos, MOUSE);

  cursor_pos = mouse_pos;

  // cursor->xPos(mouse_pos.x - 36);
  // cursor->yPos(mouse_pos.y - 36);
}

void UIManager::keyHandler(ASGE::SharedEventData data)
{
  const auto* key = dynamic_cast<const ASGE::KeyEvent*>(data.get());
  if (commandBox != nullptr)
  {
    if (
      key->key != ASGE::KEYS::KEY_ESCAPE && key->key != ASGE::KEYS::KEY_ENTER &&
      key->key != ASGE::KEYS::KEY_BACKSPACE && key->action == ASGE::KEYS::KEY_PRESSED)
    {
      commandBox->addToInput(char(key->key));
    }
    if (key->key == ASGE::KEYS::KEY_BACKSPACE && key->action == ASGE::KEYS::KEY_PRESSED)
    {
      commandBox->delFromInput();
    }
    if (key->key == ASGE::KEYS::KEY_BACKSPACE && key->action == ASGE::KEYS::KEY_REPEATED)
    {
      commandBox->delFromInput();
    }
    if (key->key == ASGE::KEYS::KEY_ENTER)
    {
      SendMessageCmd::execute(*state_manager->getNetCom(), commandBox->getText());
      commandBox->clearInput();
    }
  }
}

UIObject* UIManager::returnHandleEvent(const ASGE::Point2D& event_point, int event_type)
{
  UIObject* ui_return_handle = nullptr;

  if (selected_element != nullptr)  /// if there's a selected
  {
    if (isInside(selected_element->spriteComponent()->getSprite(), event_point))
    {
      /// if the mouse is within the element

      ui_return_handle = selected_element;
    }

    /// v this ugly mess is a no else after return
    else
    {
      /// if the mouse is outside of the currently set selected_element
      selected_element->onMouseOut();
      return nullptr;
    }
  }

  for (auto it = ui_elements.begin(); it != ui_elements.end(); ++it)
  {
    if (isInside((*it)->spriteComponent()->getSprite(), event_point))
    {
      /// Event is on selected ui_element
      switch (event_type)
      {
      case CLICK:
      {
        (*it)->onMouseClick();
        ui_return_handle = *it;
        it               = ui_elements.end() - 1;

        break;
      }
      case MOUSE:
      {
        (*it)->onMouseOver();
        ui_return_handle = *it;
        it               = ui_elements.end() - 1;
        break;
      }
      default:
      {
        // ui_return_handle = nullptr;
        break;
      }
      }
    }
  }
  return ui_return_handle;
}

bool UIManager::isInside(ASGE::Sprite* btn, ASGE::Point2D point) const
{
  auto bbox = btn->getGlobalBounds();

  return point.x >= bbox.v1.x && point.x <= bbox.v2.x && point.y >= bbox.v1.y &&
         point.y <= bbox.v3.y;
}

void UIManager::enableInput(ASGE::Input* input)
{
  if (input != nullptr)
  {
    mouse_handler_idx = input->addCallbackFnc(ASGE::E_MOUSE_MOVE, &UIManager::mouseHandler, this);

    mouse_click_handle = input->addCallbackFnc(ASGE::E_MOUSE_CLICK, &UIManager::clickHandler, this);

    key_handler_index = input->addCallbackFnc(ASGE::E_KEY, &UIManager::keyHandler, this);
  }
}

void UIManager::disableInput(ASGE::Input* input)
{
  if (input != nullptr)
  {
    input->unregisterCallback(mouse_handler_idx);
    input->unregisterCallback(mouse_click_handle);
    input->unregisterCallback(mouse_handler_idx);
    input->unregisterCallback(mouse_click_handle);
    input->unregisterCallback(key_handler_index);
    input->unregisterCallback(key_handler_index);
    input->setCursorMode(ASGE::MOUSE::CursorMode::NORMAL);
  }
}

bool UIManager::loadFonts(ASGE::Renderer* renderer)
{
  // start by creating a file handle and attempting to open the font
  using File = ASGE::FILEIO::File;
  File file  = File();
  if (file.open("/data/fonts/kenvector_future.ttf", ASGE::FILEIO::File::IOMode::READ))
  {
    // the file is open, but we need to read the contents of it into memory
    // we will use an IOBuffer for this, it will store the binary data read
    using Buffer  = ASGE::FILEIO::IOBuffer;
    Buffer buffer = file.read();

    // if we have data, load the font
    if (buffer.length != 0U)
    {
      menu_font_index = renderer->loadFontFromMem(
        "kenvector", buffer.as_unsigned_char(), static_cast<unsigned int>(buffer.length), 128);
    }

    file.close();
    return true;
  }
  return false;
}

void UIManager::changeState(int state_change)
{  /// NOTE THIS IS FOR CHANGE STATE, NOT PUSH STATE

  switch (state_change)
  {
  case GS_START_UP: state->changeState(state_manager, GS_START_UP); break;
  case GS_MENU: state->changeState(state_manager, GS_MENU); break;
  case GS_LOBBY: state->changeState(state_manager, GS_LOBBY); break;
  case GS_PARTY_MANAGER: state->changeState(state_manager, GS_PARTY_MANAGER); break;
  case GS_IN_WORLD: state->changeState(state_manager, GS_IN_WORLD); break;
  case GS_IN_BATTLE: state->changeState(state_manager, GS_IN_BATTLE); break;
  default: GS_NULL;
  }
}

UIManager* UIManager::getSelf()
{
  return this;
}

nlohmann::json UIManager::loadUI(const std::string& file_name)
{
  using File = ASGE::FILEIO::File;
  File file  = File();

  if (file.open(file_name + ".json"))
  {
    // load the file into a buffer object and convert into string
    using Buffer  = ASGE::FILEIO::IOBuffer;
    Buffer buffer = file.read();

    // parse the loaded string, you could
    nlohmann::json game_data =
      nlohmann::json::parse(buffer.as_char(), buffer.as_char() + buffer.length);

    file.close();
    return game_data;
  }
  Logging::ERRORS("Could not open file");
}

void UIManager::setNetComms(NetworkCommunicator* net_comm)
{
  net_comms = net_comm;
}
