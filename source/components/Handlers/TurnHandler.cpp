//
// Created by joemi on 26/04/2020.
//

#include <gamelib/Handlers/TurnHandler.h>
#include <random>

void TurnHandler::addToBattle(Entity* entity)
{
  entities.push_back(entity);
  number_of_entities++;
}
bool TurnHandler::initBattle()
{
  turn = 0;
  return (entities.empty());
}

void TurnHandler::endBattle()
{
  turn = -1;
  entities.clear();
}

TurnHandler::BattleStates TurnHandler::nextTurn()
{
  for (auto& entity : entities)
  {
    entity->toggleTurn(false);
    if (entity->getEntityStats()->isAlive)
    {
      entity->getTile()->spriteComponent()->getSprite()->colour(ASGE::COLOURS::WHITESMOKE);
    }
    else
    {
      entity->spriteComponent()->getSprite()->colour(ASGE::COLOURS::DARKRED);
      TurnHandler::BattleStates state = removeFromBattle(entity);
      if (state == TurnHandler::BattleStates::RUNNING)
      {
        turn++;
        return RUNNING;
      }
      return state;
    }
  }

  if (turn >= number_of_entities)
  {
    Logging::INFO(std::to_string(entities.size()));
    newCycle();
  }
  entities.at(turn)->toggleTurn(true);
  entities.at(turn)->getTile()->spriteComponent()->getSprite()->colour(ASGE::COLOURS::BLUE);
  turn++;
}

void TurnHandler::newCycle()
{
  resetCounter();
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 1);
  std::shuffle(entities.begin(), entities.end(), std::mt19937(dis(gen)));
}

TurnHandler::BattleStates TurnHandler::removeFromBattle(Entity* _entity)
{
  int i = 0;

  int number_of_players = 0;
  int number_of_enemies = 0;

  for (auto& entity : entities)
  {
    if (entity == _entity)
    {
      entities.erase(entities.begin() + i);
    }
    else if (entity->getEntityStats()->type == Entity::EntityType::ENEMY)
    {
      number_of_enemies++;
    }
    else if (entity->getEntityStats()->type == Entity::EntityType::PLAYER)
    {
      number_of_players++;
    }
    i++;
  }

  if (number_of_enemies == 0)
  {
    Logging::INFO("win");
    return TurnHandler::WIN;
  }

  if (number_of_players == 0)
  {
    return TurnHandler::LOSE;
  }

  number_of_entities--;
  return TurnHandler::RUNNING;
}
std::vector<Enemy*> TurnHandler::getEnemies()
{
  std::vector<Enemy*> enemies;
  for (auto& entity : entities)
  {
    if (entity->getEntityStats()->type == Entity::EntityType::ENEMY)
    {
      auto* enemy = dynamic_cast<Enemy*>(entity);
      enemies.emplace_back(std::ref(enemy));
    }
  }
  return enemies;
}