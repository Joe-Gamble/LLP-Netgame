//
// Joe Gamble - 22/04/20
//

#include <gamelib/Handlers/WeaponHandler.h>
#include <gamelib/Player/Entity.h>

Player::Player(RenderData* _RD, int _id, const nlohmann::json& player_data) :
  player_id(_id),
  player_elements(_RD)
{
  auto player_filename = player_data["sprite"]["filename"].get<std::string>();
  auto player_name     = player_data["sprite"]["name"].get<std::string>();

  this->getData()->name     = player_name;
  this->getData()->filename = player_filename;

  this->getEntityStats()->type = PLAYER;

  nlohmann::json inventory_data = player_data["inventory"];

  Vector3 pos = {inventory_data["pos"]["x"].get<float>(),
                 inventory_data["pos"]["y"].get<float>(),
                 inventory_data["pos"]["z"].get<float>()};

  int rows           = inventory_data["slots"]["rows"].get<int>();
  auto slot_size     = inventory_data["slots"]["size"].get<float>();
  auto slot_filename = inventory_data["slots"]["slot_sprite"].get<std::string>();

  int bag_level = inventory_data["bag"]["level"].get<int>();
  inventory     = Inventory(_RD, pos, rows, slot_size);
}

void Entity::move(TileComponent::Tile* tile)
{
  currentSlot = tile;
  this->setPos(tile->tileRect.getCenter());

  float ypos = spriteComponent()->getSprite()->yPos();
  float xpos = spriteComponent()->getSprite()->xPos();

  entity_hand.setPos(this->getPos());

  float width  = spriteComponent()->getSprite()->width();
  float height = spriteComponent()->getSprite()->height();

  this->spriteComponent()->getSprite()->yPos(ypos - height / 2);
  this->spriteComponent()->getSprite()->xPos(xpos - width / 2);

  this->setPos({spriteComponent()->getSprite()->xPos(),
                spriteComponent()->getSprite()->yPos(),
                tile->tileRect.getCenter().z});
}

void Player::addItem(ItemType itemType, int item_id)
{
  switch (itemType)
  {
  case ItemType ::WEAPON:
  {
    inventory.addItem(getWeaponHandler()->getWeapon(item_id));
    break;
  }
  case ItemType ::UTILITY:
  {
    inventory.addItem(getUtilityHandler()->getUtility(item_id));
    break;
  }
  case ItemType ::TREASURE:
  {
    /// No time
    inventory.addItem(getUtilityHandler()->getUtility(item_id + 1));
    break;
  }
  }
}

void Player::pickWeapon(ObjectPool* entities, ObjectPool* player_elements, Item* item)
{
  if (item == nullptr)
  {
    player_elements->removeObject(getHand()->item_in_hand);
    getHand()->item_in_hand = nullptr;

    for (auto& entity : *entities->getObjects())
    {
      auto* this_entity = dynamic_cast<Entity*>(&entity.get());
      if (this_entity != this)
      {
        this_entity->getTile()->spriteComponent()->getSprite()->colour(ASGE::COLOURS::WHITESMOKE);
      }
    }
    return;
  }
  entity_hand.setItem(player_elements, item);

  for (auto& entity : *entities->getObjects())
  {
    auto* this_entity = dynamic_cast<Entity*>(&entity.get());
    if (this_entity != this)
    {
      this_entity->getTile()->spriteComponent()->getSprite()->colour(ASGE::COLOURS::WHITESMOKE);
    }
  }

  if (item->getItemStats()->itemType == ItemType::WEAPON)
  {
    for (auto& entity : *entities->getObjects())
    {
      auto* this_entity = dynamic_cast<Entity*>(&entity.get());
      if (this_entity != this && this_entity->getEntityStats()->isAlive)
      {
        this_entity->getTile()->spriteComponent()->getSprite()->colour(ASGE::COLOURS::RED);
      }
    }
  }
}

void Player::addExperience(int xp)
{
  experience += xp;

  // level up player if xp is higher than 99
  if (experience > 99)
  {
    experience = 0;
    playerLevel += 1;

    // player's level cap
    if (playerLevel >= 10)
    {
      playerLevel = 10;
    }
  }
}

void Player::loseExperience(int xp)
{
  experience -= xp;

  if (experience < 0)
  {
    // keeps track of how much xp you have after you lose a level
    experience = 100 - (0 - experience);
    // lose a level
    playerLevel -= 1;

    // prevents negative levels
    if (playerLevel < 1)
    {
      playerLevel = 1;
      experience  = 0;
    }
  }
}

void Hand::setItem(ObjectPool* player_elements, Item* item)
{
  if (item_in_hand != nullptr)
  {
    player_elements->removeObject(item_in_hand);
    item_in_hand = nullptr;
  }

  player_elements->addNewObject(*item);
  item_in_hand = dynamic_cast<ItemReference*>(&player_elements->getObjects()->back().get());
  item_in_hand->setPos(hand_pos);
}

void Player::useItem()
{
  if (getHand()->item_in_hand != nullptr)
  {
    auto* item = dynamic_cast<Item*>(getHand()->item_in_hand->item);

    switch (item->getItemStats()->itemType)
    {
    case ItemType::WEAPON:
    {
      auto* weapon = dynamic_cast<Weapon*>(getHand()->item_in_hand->item);
      getSelected()->takeDamage(weapon->getDamage());

      if (getSelected()->getEntityStats()->health <= 0)
      {
        getSelected()->getEntityStats()->health  = 0;
        getSelected()->getEntityStats()->isAlive = false;
      }
    }
    case ItemType::UTILITY:
    {
      auto* utility = dynamic_cast<Utility*>(getHand()->item_in_hand->item);
      Logging::INFO(std::to_string(getSelected()->getEntityStats()->health));
    }
    case ItemType::TREASURE:
    {
      /// PLACEHOLDER
      auto* treasure = dynamic_cast<Utility*>(getHand()->item_in_hand->item);
      Logging::INFO(std::to_string(getSelected()->getEntityStats()->health));
    }
    default:
    {
      break;
    }
    }
  }
}