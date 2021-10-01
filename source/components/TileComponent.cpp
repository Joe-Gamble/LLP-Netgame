//
// Joe Gamble - 26/03/2020
//

#include "gamelib/Components/TileComponent.h"

#include "gamelib/Vector.hpp"

#include <Engine/Logger.hpp>
#include <gamelib/Player/Entity.h>

/**
 * TILE COMPONENT
 *
 * @brief TileComponent Initialization
 *
 * @param   dimensions: the size of the grid in units (X: width, Y height, Z depth)
 * @param   startPos: the starting positioon of the grid withing world space (X pos, Y pos)
 * @param   x_tiles quantity of tiles horizontally
 * @param   y_tiles quantity of tiles you want vertically
 *
 * @returns Nothing.
 */

void TileComponent::init(const Vector3& d, const Vector2& startPos, int x_tiles, int y_tiles)
{
  /// Reserve the amount of tiles needed for the component
  int number_of_tiles = x_tiles * y_tiles;
  tiles.reserve(number_of_tiles);
  dimensions = d;

  /// Push a default tile onto each allocated slot for manipulation
  for (int i = 0; i < number_of_tiles; i++)
  {
    Tile tile = Tile();
    tiles.push_back(tile);
  }

  /// Change the positional data of each tile based on its value in accordance to the rest of the
  /// vector

  Vector3 pos    = {startPos, 0};
  int id         = 0;
  float x_offset = 10;

  float width  = dimensions.x / float(x_tiles);
  float height = dimensions.y / float(y_tiles);
  int row      = 1;

  for (auto& tile : tiles)
  {
    tile.tileID = id;

    /// Is the tile at the start of a new row?
    if (id % x_tiles == 0)
    {
      // float depth = (dimensions.z - pos.z) / dimensions.z;
      pos.x = startPos.x;
      pos.x += ((width - (width / 4) * float(row)));

      pos.z += (dimensions.z / float(y_tiles));
      height *= 1.0F - ((float(row) / 2) / float(y_tiles));
      pos.y -= height;
      //(height * float(y_tiles) / float(row));
      row++;
    }
    else  /// move the tile's x value
    {
      pos.x += (width - (width / 4));
    }

    tile.tilePos.operator=(pos);
    tile.tileRect        = {tile.tilePos, width, height};
    id++;
  }
}

Vector3& TileComponent::getDimensions()
{
  return dimensions;
}
std::vector<TileComponent::Tile>* TileComponent::getTiles()
{
  return &tiles;
}
void TileComponent::updateTileVisals(Item* item, ObjectPool* entities)
{
  if (item->getItemStats()->itemType == WEAPON)
  {
    for (auto& entity : *entities->getObjects())
    {
      auto* en = dynamic_cast<Entity*>(&entity.get());
      en->getTile()->spriteComponent()->getSprite()->colour(ASGE::COLOURS::RED);
    }
  }
}

/*
void TileComponent::Tile::addObject(GameObject* go)
{
  stored_gos.push_back(go);
}
*/