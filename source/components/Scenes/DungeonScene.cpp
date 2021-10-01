//
// Joe Gamble 21/04/20
//

#include <../apps/ASGEGame/Managers/SceneManager.hpp>
#include <Engine/Logger.hpp>
#include <gamelib/Player/Entity.h>

void Dungeon::initDungeon(
  ASGE::Renderer* renderer,
  TurnHandler* _turnHandler,
  const nlohmann::json& dungeon_data)
{
  int difficulty = dungeon_data["difficulty"].get<int>();

  nlohmann::json grid_info = dungeon_data["grid_info"];

  auto d_x = grid_info["d_x"].get<float>();
  auto d_y = grid_info["d_y"].get<float>();
  auto d_z = grid_info["d_z"].get<float>();

  auto start_pos_x = grid_info["start_pos_x"].get<float>();
  auto start_pos_y = grid_info["start_pos_y"].get<float>();
  auto x_tiles     = grid_info["x_tiles"].get<int>();
  auto y_tiles     = grid_info["y_tiles"].get<int>();

  getTileComponent()->init({d_x, d_y, d_z}, {start_pos_x, start_pos_y}, x_tiles, y_tiles);

  for (auto& tile : *getTileComponent()->getTiles())
  {
    tile.instantiate(renderer, "tile.png", tile.tilePos.x, tile.tilePos.y);
    tile.setSize({tile.tileRect.length, tile.tileRect.height});
  }

  nlohmann::json enemy_info = dungeon_data["dungeon_details"];

  int enemy_total = enemy_info["NumberOfEnemies"].get<int>();

  for (int i = 0; i < enemy_total; i++)
  {
    int enemy_type = enemy_info["enemies"][i]["type"].get<int>();
    int tile       = enemy_info["enemies"][i]["tile_start"].get<int>();

    getEntityPool()->addRenderedObject(&enemyHandler.getEnemy(enemy_type).get());

    auto* enemy = dynamic_cast<Enemy*>(&getEntityPool()->getObjects()->back().get());

    enemy->setSize({100, 100});
    enemy->move(getTileComponent()->getTilePosAtID(tile));
    enemy->getHand()->setPos(enemy->getPos());
  }

  turnHandler = _turnHandler;
}

TileComponent* Dungeon::getTileComponent()
{
  return &tileComponent;
}

void Dungeon::init(
  SceneManager* sceneManager,
  SceneTypes sceneType,
  int scene_id,
  const std::string& filename)
{
  this->setSceneManager(sceneManager);
  this->getProps()->scene_type = sceneType;
  this->getProps()->scene_id   = scene_id;
  this->getProps()->filename   = filename;
}

void Dungeon::render(RenderData* _RD)
{
  _RD->p_renderer->renderSprite(*this->getBackground()->spriteComponent()->getSprite());

  for (auto& tile : *getTileComponent()->getTiles())
  { _RD->p_renderer->renderSprite(*tile.spriteComponent()->getSprite()); }

  for (auto& player : *getPlayers())
  {
    _RD->p_renderer->renderSprite(*player->spriteComponent()->getSprite());
    for (auto& element : *player->getElements()->getObjects())
    { _RD->p_renderer->renderSprite(*element.get().spriteComponent()->getSprite()); }

    for (auto& slot : *player->getInventory()->getSlots())
    {
      _RD->p_renderer->renderSprite(*slot.spriteComponent()->getSprite());
      if (slot.getSlotStats()->occupied)
      {
        _RD->p_renderer->renderSprite(*slot.getRef()->spriteComponent()->getSprite());
      }
    }
  }

  for (auto& entity : *getEntityPool()->getObjects())
  { _RD->p_renderer->renderSprite(*entity.get().spriteComponent()->getSprite()); }

  _RD->p_renderer->renderText(status, 500, 300, ASGE::COLOURS::LIGHTBLUE);
}

void Dungeon::enterDungeon()
{
  for (auto& entity : *getEntityPool()->getObjects())
  { getTurnHandler()->addToBattle(dynamic_cast<Entity*>(&entity.get())); }

  for (auto& player : *getPlayers()) { player->move(tileComponent.getTilePosAtID(8)); }
  if (turnHandler->initBattle())
  {
    turnHandler->newCycle();
  }
}

void Dungeon::update(double dt) {}

void Dungeon::keyHandler(ASGE::SharedEventData data)
{
  const auto* key = dynamic_cast<const ASGE::KeyEvent*>(data.get());
  Player* player  = getPlayers()->at(0).get();

  if (key->key == ASGE::KEYS::KEY_D && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    getPlayers()->at(0)->getInventory()->setBagLevel(2);
  }
}
void Dungeon::clickHandler(ASGE::SharedEventData data)
{
  auto click     = dynamic_cast<const ASGE::ClickEvent*>(data.get());
  Player* player = getPlayers()->at(0).get();

  if (click->action == ASGE::MOUSE::BUTTON_PRESSED && player->getTurn())
  {
    if (player->getSelected() != nullptr)
    {
      player->useItem();
      player->setSelected(nullptr);
      player->pickWeapon(&entities, player->getElements(), nullptr);
      TurnHandler::BattleStates state = turnHandler->nextTurn();

      if (state == TurnHandler::RUNNING)
      {
        return;
      }

      if (state == TurnHandler::WIN)
      {
        status = "YOU WIN!";
      }
      else if (state == TurnHandler::LOSE)
      {
        status = "YOU LOSE!";
      }
    }
    std::vector<Inventory::Slot>* slots = player->getInventory()->getSlots();
    for (int i = 0; i < player->getInventory()->getBag()->getBagStats()->bag_size; i++)
    {
      if (slots->at(i).getSlotStats()->highlighted && slots->at(i).getSlotStats()->occupied)
      {
        slots->at(i).getSlotStats()->selected = !slots->at(i).getSlotStats()->selected;
        if (slots->at(i).getSlotStats()->selected)
        {
          slots->at(i).spriteComponent()->getSprite()->colour(ASGE::COLOURS::BLUE);
          player->pickWeapon(
            &entities, player->getElements(), dynamic_cast<Item*>(slots->at(i).getRef()->item));
        }
        else if (!slots->at(i).getSlotStats()->selected)
        {
          slots->at(i).spriteComponent()->getSprite()->colour(ASGE::COLOURS::WHITESMOKE);
          player->pickWeapon(&entities, player->getElements(), nullptr);
        }
      }
    }
  }
}

void Dungeon::mouseHandler(ASGE::SharedEventData data)
{
  const auto* mouse                   = dynamic_cast<const ASGE::MoveEvent*>(data.get());
  float scalar                        = 1.1F;
  Vector3 mouse_pos                   = {float(mouse->xpos), float(mouse->ypos), 0};
  Player* player                      = getPlayers()->at(0).get();
  std::vector<Inventory::Slot>* slots = player->getInventory()->getSlots();

  for (int i = 0; i < player->getInventory()->getBag()->getBagStats()->bag_size; i++)
  {
    if (!slots->at(i).getSlotStats()->highlighted && slots->at(i).getSlotZone().isInside(mouse_pos))
    {
      slots->at(i).scalar(scalar);
      slots->at(i).getSlotStats()->highlighted = true;
      if (slots->at(i).getSlotStats()->occupied)
      {
        slots->at(i).getRef()->scalar(scalar);
      }
    }
    else if (!(slots->at(i).getSlotZone().isInside(mouse_pos)))
    {
      if (!slots->at(i).getSlotStats()->selected)
      {
        slots->at(i).resetScalar();
        slots->at(i).getSlotStats()->highlighted = false;
        if (slots->at(i).getSlotStats()->occupied)
        {
          slots->at(i).getRef()->resetScalar();
        }
      }
    }
  }
  if (player->getHand()->item_in_hand != nullptr)
  {
    mouseInside(player, mouse_pos, scalar);
  }
}
void Dungeon::scrollHandler(ASGE::SharedEventData data) {}

bool Dungeon::mouseInside(Player* player, Vector3& mouse_pos, float scalar)
{
  Item* item = dynamic_cast<Item*>(player->getHand()->item_in_hand->item);
  switch (item->getItemStats()->itemType)
  {
  case ItemType::WEAPON:
  {
    for (auto& enemy : turnHandler->getEnemies())
    {
      if (enemy->spriteComponent()->getBoundingBox().isInside(mouse_pos))
      {
        enemy->scalar(scalar);
        player->setSelected(enemy);
        return true;
      }
      enemy->resetScalar();
      player->setSelected(nullptr);
    }
    return false;
  }
  case ItemType::UTILITY:
  {
    for (auto& entities : *turnHandler->getTurnEntities())
    {
      if (entities->spriteComponent()->getBoundingBox().isInside(mouse_pos))
      {
        entities->scalar(scalar);
        player->setSelected(entities);
        return true;
      }
      entities->resetScalar();
      player->setSelected(nullptr);
    }
    return false;
  }
  }
}
SceneObject* Dungeon::mouseOutside(Player* player, Vector3& mouse_pos)
{
  auto* ref = dynamic_cast<Item*>(player->getHand()->getItem());
  for (auto& enemy : turnHandler->getEnemies())
  {
    if (enemy->spriteComponent()->getBoundingBox().isInside(mouse_pos))
    {
      return enemy;
    }
  }
  return nullptr;
}
