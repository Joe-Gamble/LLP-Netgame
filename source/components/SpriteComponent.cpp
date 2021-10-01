//
// Created by joemi on 22/03/2020.
//

#include "gamelib/Components/SpriteComponent.hpp"

#include "gamelib/Vector.hpp"

#include <Engine/Renderer.h>

SpriteComponent::~SpriteComponent()
{
  free();
}

bool SpriteComponent::loadSprite(ASGE::Renderer* renderer, const std::string& texture_file_name)
{
  free();
  sprite = renderer->createRawSprite();
  if (sprite->loadTexture(texture_file_name))
  {
    return true;
  }

  free();
  return false;
}

bool SpriteComponent::loadSprite(
  ASGE::Renderer* renderer,
  const std::string& texture_file_name,
  const Vector2& coords,
  float width,
  float height)
{
  free();
  sprite = renderer->createRawSprite();
  if (sprite->loadTexture(texture_file_name))
  {
    sprite->srcRect()[0] = coords.x;
    sprite->srcRect()[1] = coords.y;
    sprite->srcRect()[2] = width;
    sprite->srcRect()[3] = height;
    return true;
  }

  free();
  return false;
}

void SpriteComponent::free()
{
  if (sprite != nullptr)
  {
    delete sprite;
    sprite = nullptr;
  }
}

ASGE::Sprite* SpriteComponent::getSprite()
{
  if (sprite != nullptr)
  {
    return sprite;
  }
}

Rect SpriteComponent::getBoundingBox() const
{
  Rect bounding_box;
  bounding_box.origin.x = sprite->xPos();
  bounding_box.origin.y = sprite->yPos();
  bounding_box.length   = sprite->width();
  bounding_box.height   = sprite->height();

  return bounding_box;
}
