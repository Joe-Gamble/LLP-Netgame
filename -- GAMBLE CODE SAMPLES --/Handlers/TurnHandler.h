//
// Joe Gamble - 26/04/2020
//

#ifndef MYNETGAME_TURNHANDLER_H
#define MYNETGAME_TURNHANDLER_H

#include <gamelib/Handlers/EnemyHandler.h>
#include <gamelib/Player/Entity.h>
#include <vector>

class TurnHandler
{
 public:
  enum BattleStates
  {
    RUNNING = 0,
    LOSE    = 1,
    WIN     = 2
  };
  TurnHandler()  = default;
  ~TurnHandler() = default;

  bool initBattle();
  void addToBattle(Entity* entity);
  void endBattle();
  void resetCounter() { turn = 0; }
  BattleStates nextTurn();
  void newCycle();
  int getCurrentTurn() { return turn; }

  TurnHandler::BattleStates removeFromBattle(Entity* entity);

  std::vector<Enemy*> getEnemies();
  std::vector<Entity*>* getTurnEntities() { return &entities; }
  Entity* getCurrentTurnEntity() { return entities.at(turn); }

 private:
  int turn               = -1;
  int number_of_entities = 0;
  std::vector<Entity*> entities;
};

#endif  // MYNETGAME_TURNHANDLER_H
