//
// Created by miles on 05/04/2020.
//

#ifndef MYNETGAME_UIOBJECT_H
#define MYNETGAME_UIOBJECT_H

#include "gamelib/Components/SpriteComponent.hpp"
#include "gamelib/GameData.h"
#include "gamelib/RenderData.h"

class GameData;
class RenderData;
class UIManager;

struct UiProperties
{
  UiProperties(float _x, float _y, float _w, float _h, std::string file_path);
  float m_x      = 0;
  float m_y      = 0;
  float m_width  = 0;
  float m_height = 0;
  const std::string texture_file_path;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
/// This UI object class is the base class for each UI element
/// This is an abstract class to interface the UI elements from the UI
/// Manager.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class UIObject
{
 public:
  UIObject()          = default;
  virtual ~UIObject() = default;
  /// Clang Tidy destructor issue work-around
  UIObject(UIObject const&) = default;
  UIObject& operator=(UIObject const&) = default;
  UIObject(UIObject&&)                 = default;
  UIObject& operator=(UIObject&&) = default;

  virtual void setUpObject(RenderData* _RD);
  virtual void cleanUpObject();

  /// Basic update & render interface
  virtual void update(GameData* _GD)   = 0;
  virtual void render(RenderData* _RD) = 0;

  /// Base event call interface
  virtual void onMouseOver()  = 0;
  virtual void onMouseOut()   = 0;
  virtual void onMouseClick() = 0;
  // virtual void onDragEnd() = 0;
  // virtual void onDragStart() = 0;

  /// Sprite component functions, access, init, free
  SpriteComponent* spriteComponent();
  bool initSprite(ASGE::Renderer* renderer);
  void free();

 protected:
  UIManager* ui_manager          = nullptr;  /// Link to the ui_managers interface
  const UiProperties* properties = nullptr;

  bool interactable = false;  /// doesnt interact with user inputs / @todo move into properties
  bool selected     = false;

  SpriteComponent* sprite_component = nullptr;

 private:
};

#endif  // MYNETGAME_UIOBJECT_H
