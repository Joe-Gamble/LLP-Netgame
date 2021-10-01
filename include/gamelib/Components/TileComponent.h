//
// Joe Gamble - 26/03/20
//

#ifndef MYNETGAME_TILECOMPONENT_H
#define MYNETGAME_TILECOMPONENT_H

#include "gamelib/GameObject.hpp"
#include "gamelib/Rect.hpp"
#include "gamelib/Vector.hpp"

#include <gamelib/Player/Inventory.h>

/**
 *  @brief TileComponent sets up the scene for manipulation regarding positional data
 */

class TileComponent
{
 public:
  struct Tile : public GameObject
  {
    Tile()          = default;
    int tileID      = 0;
    Vector3 tilePos = {0, 0, 0};
    Rect tileRect   = {tilePos, 0, 0};

    // void addObject(GameObject* go);

    // do you really mean shared? shared pointers should never really be used as they saw
    // two or more parts of the codebase are responsible for memory assigned, but actually
    // the memory is managed with the scene creation and destruction!
   private:
    std::vector<GameObject*> stored_gos{nullptr};
  };
  // void removeObject();
  TileComponent() = default;
  void init(const Vector3& dimensions, const Vector2& startPos, int x_tiles, int y_tiles);
  std::vector<Tile>* getTiles();
  TileComponent::Tile* getTilePosAtID(int id) { return &tiles.at(id); }
  void updateTileVisals(Item* item, ObjectPool* entities);
  Vector3& getDimensions();

 private:
  std::vector<Tile> tiles;
  Vector3 dimensions = {0, 0, 0};
};

#endif  // MYNETGAME_TILECOMPONENT_H
