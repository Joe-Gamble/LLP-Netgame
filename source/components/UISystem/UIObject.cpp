//

#include <gamelib/UISystem/UIObject.h>
//
// Created by miles on 05/04/2020.
UiProperties::UiProperties(float _x, float _y, float _w, float _h, std::string file_path) :
  m_x(_x),
  m_y(_y),
  m_width(_w),
  m_height(_h),
  texture_file_path(std::move(file_path))
{
}

void UIObject::setUpObject(RenderData* _RD) {}

void UIObject::cleanUpObject() {}

bool UIObject::initSprite(ASGE::Renderer* renderer)
{
  free();
  sprite_component = new SpriteComponent();
  if (sprite_component->loadSprite(renderer, properties->texture_file_path))
  {
    if (sprite_component != nullptr)
    {
      sprite_component->getSprite()->xPos(properties->m_x);
      sprite_component->getSprite()->yPos(properties->m_y);
      sprite_component->getSprite()->width(properties->m_width);
      sprite_component->getSprite()->height(properties->m_height);

      return true;
    }
  }
  return false;
}

void UIObject::free()
{
  if (sprite_component != nullptr)
  {
    delete sprite_component;
    sprite_component = nullptr;
  }
}

SpriteComponent* UIObject::spriteComponent()
{
  return sprite_component;
}
