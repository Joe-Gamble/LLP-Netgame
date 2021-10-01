//
// Joe Gamble 28/04/2020
//

#include "gamelib/Handlers/EnemyHandler.h"

EnemyHandler::EnemyHandler()
{
  nlohmann::json enemy_data = init("Json/Enemydata")["Enemies"];
  number_of_enemies         = enemy_data["Number_Of_Enemies"].get<int>();

  enemy_list.getObjects()->reserve(number_of_enemies);

  /// WEAPON SETUP

  Enemy* orc = new Orc();
  enemy_list.addObject(orc);
  Enemy* skeleton = new Skeleton();
  enemy_list.addObject(skeleton);

  int id = 0;
  for (auto& weapon : *getEnemies())
  {
    weapon.get().operator=(*createEnemy(dynamic_cast<Enemy*>(&weapon.get()), enemy_data, id));
    id++;
  }
}

Enemy* EnemyHandler::createEnemy(Enemy* _enemy, const nlohmann::json& data, int enemy_id)
{
  // retarget the json for the particular weapon
  nlohmann::json enemy_data = data["Enemy"][enemy_id];

  // store the desired variables
  auto name     = enemy_data["name"].get<std::string>();
  auto filename = enemy_data["sprite"]["filename"].get<std::string>();

  auto health = enemy_data["stats"]["health"].get<float>();
  auto dodge  = enemy_data["stats"]["dodge"].get<float>();
  auto speed  = enemy_data["stats"]["speed"].get<float>();

  _enemy->init(name, filename, health, dodge, speed, enemy_id);

  return _enemy;
}

void Enemy::init(
  const std::string& n,
  const std::string& fn,
  float health,
  float dodge,
  float speed,
  int id)
{
  getData()->filename = fn;
  getData()->name     = n;
  enemy_id            = id;

  getEntityStats()->health = health;
  getEntityStats()->speed  = speed;
  getEntityStats()->dodge  = dodge;
  getEntityStats()->type   = ENEMY;
}

nlohmann::json EnemyHandler::init(const std::string& file_name)
{
  using File = ASGE::FILEIO::File;
  File file  = File();

  if (file.open(file_name + ".json"))
  {
    // load the file into a buffer object and convert into string
    using Buffer  = ASGE::FILEIO::IOBuffer;
    Buffer buffer = file.read();

    // parse the loaded string, you could
    nlohmann::json game_data =
      nlohmann::json::parse(buffer.as_char(), buffer.as_char() + buffer.length);

    file.close();
    return game_data;
  }
  Logging::ERRORS("Could not open file");
}

Enemy::Enemy(ObjectPool* dungeon_pool, int _id, const nlohmann::json& enemy_data) {}

int Enemy::returnExperience()
{
  return experienceAmmount;
}
