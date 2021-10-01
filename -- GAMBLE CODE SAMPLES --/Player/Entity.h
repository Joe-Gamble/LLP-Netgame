//
// // Joe Gamble 21/04/20
//

#ifndef MYNETGAME_ENTITY_H
#define MYNETGAME_ENTITY_H

#include "Inventory.h"

#include <gamelib/Components/TileComponent.h>
#include <gamelib/GameObject.hpp>
#include <gamelib/Handlers/UtilityHandler.h>
#include <gamelib/Handlers/WeaponHandler.h>
#include <nlohmann/json.hpp>

class Entity;

struct Hand
{
  explicit Hand(Entity* _entity) : entity(_entity) {}
  Vector3 hand_pos = {0, 0, 0};
  void setItem(ObjectPool* player_elements, Item* item);

  ItemReference* item_in_hand = nullptr;
  Entity* entity;
  void setPos(Vector3& pos) { hand_pos = pos; }
  ItemReference* getItem()
  {
    if (item_in_hand != nullptr)
    {
      return item_in_hand;
    }
  }
};
class Entity : public SceneObject
{
 public:
  enum EntityType
  {
    UNCLASSIFIED = -1,
    PLAYER       = 0,
    ENEMY        = 1
  };

  struct EntityStats
  {
    float health    = 100.0F;
    float speed     = 1.0F;
    float dodge     = 1.0F;
    EntityType type = UNCLASSIFIED;

    bool isAlive = true;
  };

  Entity() : entity_hand(this) {}
  ~Entity() = default;

  // Health
  void takeDamage(float damage) { getEntityStats()->health -= damage; }
  void restoreHealth(float health) { stats.health += health; }

  EntityStats getStats() { return stats; }

  void move(TileComponent::Tile* tile);

  // Health
  void regainHealth(float heal) { entityStats.health += heal; }

  // Speed
  void setSpeed(float new_speed) { entityStats.speed = new_speed; }
  void increaseSpeed(float speed) { entityStats.speed += speed; }
  void decrease(float speed) { entityStats.speed -= speed; }

  // dodge
  [[nodiscard]] float getDodge() const { return entityStats.dodge; }

  WeaponHandler* getWeaponHandler() { return &m_Weapon_Handler; }
  UtilityHandler* getUtilityHandler() { return &m_UtilityHandler; }
  EntityStats* getEntityStats() { return &entityStats; }
  TileComponent::Tile* getTile()
  {
    if (currentSlot != nullptr)
    {
      return currentSlot;
    };
  }
  Hand* getHand() { return &entity_hand; }

  bool getTurn() { return turn; }
  void toggleTurn(bool _turn) { turn = _turn; }

 private:
  bool turn                        = false;
  TileComponent::Tile* currentSlot = nullptr;
  Vector3 pos                      = {
    0,
    0,
    0,
  };

 protected:
  EntityStats entityStats;
  Hand entity_hand;
  WeaponHandler m_Weapon_Handler;
  UtilityHandler m_UtilityHandler;

  EntityStats stats;
};

class Player : public Entity
{
 public:
  Player(RenderData* _RD, int _id, const nlohmann::json& player_data);
  ~Player() = default;

  void pickWeapon(ObjectPool* entities, ObjectPool* player_elements, Item* item);
  void setSelected(Entity* entity) { selected_entity = entity; }
  void addItem(ItemType itemType, int item_id);

  void useItem();

  Entity* getSelected() { return selected_entity; }
  Inventory* getInventory() { return &inventory; }
  ObjectPool* getElements() { return &player_elements; }

  void addExperience(int xp);
  void loseExperience(int _xp);

 private:
  ObjectPool player_elements;
  Inventory inventory;
  int player_id           = -1;
  Entity* selected_entity = nullptr;
  int experience          = 0;
  int playerLevel         = 0;
};

#endif  // MYNETGAME_ENTITY_H
