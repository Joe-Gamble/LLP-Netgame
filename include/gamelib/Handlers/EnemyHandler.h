//
// Created by joemi on 28/04/2020.
//

#ifndef MYNETGAME_ENEMYHANDLER_H
#define MYNETGAME_ENEMYHANDLER_H

#include <gamelib/Player/Entity.h>

class Enemy : public Entity
{
 public:
  Enemy() = default;
  Enemy(ObjectPool* dungeon_pool, int _id, const nlohmann::json& enemy_data);

  void
  init(const std::string& n, const std::string& fn, float health, float dodge, float speed, int id);
  ~Enemy() = default;

  int returnExperience();

 private:
  int enemy_id          = 0;
  int experienceAmmount = 0;
};

class Orc : public Enemy
{
 public:
  Orc()  = default;
  ~Orc() = default;

 private:
  int enemy_id = 0;
};
class Skeleton : public Enemy
{
 public:
  Skeleton()  = default;
  ~Skeleton() = default;
};

class EnemyHandler
{
 public:
  EnemyHandler();
  ~EnemyHandler() = default;

  static nlohmann::json init(const std::string& file_name);
  static Enemy* createEnemy(Enemy* _enemy, const nlohmann::json& data, int enemy_id);

  const std::vector<std::reference_wrapper<SceneObject>>* getEnemies()
  {
    return enemy_list.getObjects();
  }

  std::reference_wrapper<SceneObject> getEnemy(int id) { return enemy_list.getObjects()->at(id); }
  ObjectPool* getPool() { return &enemy_list; }

 private:
  ObjectPool enemy_list;
  int number_of_enemies = 0;
};

#endif  // MYNETGAME_ENEMYHANDLER_H
