// Joe Gamble 22/03/20
#include "gamelib/GameObject.hpp"

#include <Engine/Renderer.h>

GameObject::~GameObject()
{
  free();
}

bool GameObject::instantiate(ASGE::Renderer* renderer, const std::string& texture_file_name)
{
  free();
  sprite_component = new SpriteComponent();
  if (sprite_component->loadSprite(renderer, texture_file_name))
  {
    if (sprite_component != nullptr)
    {
      sprite_component->getSprite()->xPos(0);
      sprite_component->getSprite()->yPos(0);

      visabilty = true;
      return true;
    }
  }
  return false;
}

bool GameObject::instantiate(
  ASGE::Renderer* renderer,
  const std::string& texture_file_name,
  float xpos,
  float ypos,
  float width,
  float height)
{
  free();
  sprite_component = new SpriteComponent();
  if (sprite_component->loadSprite(renderer, texture_file_name))
  {
    if (sprite_component != nullptr)
    {
      sprite_component->getSprite()->xPos(xpos);
      sprite_component->getSprite()->yPos(ypos);
      sprite_component->getSprite()->width(width);
      sprite_component->getSprite()->height(height);

      setOriginalPos(xpos, ypos);

      visabilty = true;

      return true;
    }
  }
  return false;
}

bool GameObject::instantiate(
  ASGE::Renderer* renderer,
  const std::string& texture_file_name,
  float xpos,
  float ypos,
  float width,
  float height,
  const Vector2& coords)
{
  free();

  sprite_component = new SpriteComponent();

  if (sprite_component->loadSprite(renderer, texture_file_name, coords, width, height))
  {
    setOriginalPos(xpos, ypos);

    sprite_component->getSprite()->xPos(xpos);
    sprite_component->getSprite()->yPos(ypos);
    sprite_component->getSprite()->width(width);
    sprite_component->getSprite()->height(height);

    return true;
  }

  free();
  return false;
}

bool GameObject::instantiate(
  ASGE::Renderer* renderer,
  const std::string& texture_file_name,
  float xpos,
  float ypos)
{
  free();

  sprite_component = new SpriteComponent();

  if (sprite_component->loadSprite(renderer, texture_file_name))
  {
    setOriginalPos(xpos, ypos);

    sprite_component->getSprite()->xPos(xpos);
    sprite_component->getSprite()->yPos(ypos);
    sprite_component->getSprite()->width(spriteComponent()->getSprite()->width());
    sprite_component->getSprite()->height(spriteComponent()->getSprite()->height());

    return true;
  }

  free();
  return false;
}

void GameObject::setOriginalPos(float xpos, float ypos)
{
  original_pos.x = xpos;
  original_pos.y = ypos;
}

void GameObject::setPos(const Vector3& _pos)
{
  pos = _pos;
  setOriginalPos(pos.x, pos.y);
  spriteComponent()->getSprite()->xPos(pos.x);
  spriteComponent()->getSprite()->yPos(pos.y);
}

void GameObject::free()
{
  if (sprite_component != nullptr)
  {
    delete sprite_component;
    sprite_component = nullptr;
  }
}

SpriteComponent* GameObject::spriteComponent()
{
  if (sprite_component != nullptr)
  {
    return sprite_component;
  }
}

void GameObject::setSize(Vector2 size)
{
  this->spriteComponent()->getSprite()->width(size.x);
  this->spriteComponent()->getSprite()->height(size.y);
}

void GameObject::scalar(const float& multiplier)
{
  if (!hasScaled)
  {
    float xpos = spriteComponent()->getSprite()->xPos();
    float ypos = spriteComponent()->getSprite()->yPos();

    setOriginalPos(xpos, ypos);

    spriteComponent()->getSprite()->scale(multiplier);

    float x_diff =
      (float(spriteComponent()->getSprite()->width() * multiplier) -
       (float(spriteComponent()->getSprite()->width())));
    float y_diff =
      (float(spriteComponent()->getSprite()->height() * multiplier) -
       (float(spriteComponent()->getSprite()->height())));

    spriteComponent()->getSprite()->xPos(xpos - x_diff / 2);
    spriteComponent()->getSprite()->yPos(ypos - y_diff / 2);

    hasScaled = true;
  }
}

void GameObject::resetScalar()
{
  spriteComponent()->getSprite()->scale(1);
  spriteComponent()->getSprite()->xPos(original_pos.x);
  spriteComponent()->getSprite()->yPos(original_pos.y);
  hasScaled = false;
}

void GameObject::toggleVisable()
{
  visabilty = !visabilty;
}